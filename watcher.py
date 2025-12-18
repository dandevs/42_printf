"""
C File Watcher - Automatically compile and run C files on change

Usage:
    python3 watcher.py [directory] [--unsafe] [--fast]

Options:
    --unsafe    Disable compiler warnings (-Wall, -Wextra, -Werror)
    --fast      Enable incremental compilation optimizations:
                - -O0: No optimization for faster compilation
                - ccache: Compiler cache (if installed)
"""

import os
import sys
import time
import signal
import subprocess
import threading


class FileWatcher:
    """Watch files for changes in a background thread."""
    
    def __init__(self, directory, recursive=False):
        self.directory = directory
        self.recursive = recursive
        self.mtimes = {}
        self.changed = threading.Event()
        self.stop_event = threading.Event()
        self.thread = None
    
    def get_c_files(self):
        """Get all .c files from directory."""
        if self.recursive:
            c_files = []
            for root, dirs, files in os.walk(self.directory):
                dirs[:] = [d for d in dirs if not d.startswith('.')]
                for f in files:
                    if f.endswith('.c'):
                        c_files.append(os.path.join(root, f))
            return c_files
        else:
            return [os.path.join(self.directory, f) 
                    for f in os.listdir(self.directory) if f.endswith('.c')]
    
    def init_mtimes(self):
        """Initialize file modification times."""
        for filepath in self.get_c_files():
            try:
                self.mtimes[filepath] = os.path.getmtime(filepath)
            except OSError:
                pass
    
    def check_changes(self):
        """Check if any files have changed."""
        try:
            for filepath in self.get_c_files():
                try:
                    mtime = os.path.getmtime(filepath)
                    if filepath not in self.mtimes or mtime != self.mtimes[filepath]:
                        self.mtimes[filepath] = mtime
                        return True
                except OSError:
                    continue
        except OSError:
            pass
        return False
    
    def watch_loop(self):
        """Background thread that watches for file changes."""
        while not self.stop_event.is_set():
            if self.check_changes():
                self.changed.set()
            time.sleep(0.3)
    
    def start(self):
        """Start watching for changes."""
        self.init_mtimes()
        self.thread = threading.Thread(target=self.watch_loop, daemon=True)
        self.thread.start()
    
    def stop(self):
        """Stop watching."""
        self.stop_event.set()
        if self.thread:
            self.thread.join(timeout=1)
    
    def has_changed(self):
        """Check if files changed and clear the flag."""
        if self.changed.is_set():
            self.changed.clear()
            return True
        return False
    
    def wait_for_change(self, timeout=None):
        """Wait for a file change."""
        return self.changed.wait(timeout=timeout)


class ProcessRunner:
    """Run and manage subprocesses."""
    
    def __init__(self):
        self.process = None
    
    def run(self, cmd, cwd=None, env=None):
        """Run a command and return the process."""
        try:
            self.process = subprocess.Popen(
                cmd, cwd=cwd, env=env,
                preexec_fn=os.setsid
            )
            return self.process
        except Exception:
            return None
    
    def run_and_wait(self, cmd, cwd=None, env=None, capture=False):
        """Run a command and wait for completion. If capture=True, suppress output unless the command fails."""
        try:
            res = subprocess.run(
                cmd, cwd=cwd, env=env, check=True,
                capture_output=capture, text=True
            )
            return res
        except subprocess.CalledProcessError as e:
            # When output was captured, show both stdout and stderr on failure.
            if capture:
                if e.stdout:
                    print(e.stdout, end='')
                if e.stderr:
                    print(e.stderr, end='', file=sys.stderr)
            return None
    
    def kill(self):
        """Kill the current process and its children."""
        if self.process and self.process.poll() is None:
            try:
                os.killpg(os.getpgid(self.process.pid), signal.SIGTERM)
                self.process.wait(timeout=1)
            except (ProcessLookupError, PermissionError, OSError):
                pass
            except subprocess.TimeoutExpired:
                try:
                    os.killpg(os.getpgid(self.process.pid), signal.SIGKILL)
                except (ProcessLookupError, PermissionError, OSError):
                    pass
    
    def wait_or_interrupt(self, watcher):
        """Wait for process to finish or file change."""
        if not self.process:
            return False
        
        while self.process.poll() is None:
            if watcher.has_changed():
                self.kill()
                return True
            time.sleep(0.1)
        return False


class CCompiler:
    """Handle C compilation."""
    
    def __init__(self, flags=None, use_ccache=False):
        self.flags = flags or []
        self.use_ccache = use_ccache
        self.runner = ProcessRunner()
    
    def get_env(self):
        """Get environment with ccache if enabled."""
        env = os.environ.copy()
        if self.use_ccache:
            env['CC'] = 'ccache cc'
        if self.flags:
            existing = env.get('CFLAGS', '')
            env['CFLAGS'] = f"{existing} {' '.join(self.flags)}".strip()
        return env
    
    def make_build(self, directory):
        """Build using make, suppressing output unless there is an error."""
        env = self.get_env()
        # Always capture output during build to suppress on success
        self.runner.run_and_wait(["make", "fclean"], cwd=directory, capture=True)
        result = self.runner.run_and_wait(["make"], cwd=directory, env=env, capture=True)
        if not result:
            print("\n⚠️ Build failed. Showing compiler output above.")
            return False
        return True
    
    def make_run(self, directory, watcher):
        """Run using make and watch for changes."""
        env = self.get_env()
        # Clear terminal before running program output
        clear_screen()
        self.runner.run(["make", "run"], cwd=directory, env=env)
        return self.runner.wait_or_interrupt(watcher)
    
    def compile_file(self, filepath):
        """Compile a single C file, suppressing output unless compilation fails."""
        exe_name = os.path.splitext(filepath)[0]
        compiler = ["ccache", "cc"] if self.use_ccache else ["cc"]
        cmd = compiler + self.flags + [filepath, "-o", exe_name]
        result = self.runner.run_and_wait(cmd, capture=True)
        if not result:
            print("\n⚠️ Compilation failed. Showing compiler output above.")
            return None
        return exe_name
    
    def run_file(self, exe_name, watcher):
        """Run compiled executable and watch for changes."""
        # Clear terminal before running program output
        clear_screen()
        self.runner.run([f"./{exe_name}"])
        interrupted = self.runner.wait_or_interrupt(watcher)
        
        # Cleanup executable
        try:
            os.remove(exe_name)
        except OSError:
            pass
        
        return interrupted
    
    def kill(self):
        """Kill running process."""
        self.runner.kill()


def has_ccache():
    """Check if ccache is available."""
    try:
        subprocess.run(["ccache", "--version"], capture_output=True, check=True)
        return True
    except (subprocess.CalledProcessError, FileNotFoundError):
        return False


def has_makefile(directory):
    """Check if Makefile exists."""
    return os.path.exists(os.path.join(directory, "Makefile"))


def clear_screen():
    """Clear the terminal."""
    os.system('clear')


def parse_args():
    """Parse command line arguments."""
    args = sys.argv[1:]
    
    unsafe = "--unsafe" in args
    if unsafe:
        args.remove("--unsafe")
    
    fast = "--fast" in args
    if fast:
        args.remove("--fast")
    
    directory = args[0] if args else "."
    
    return directory, unsafe, fast


def main():
    directory, unsafe, fast = parse_args()
    
    # Setup compiler flags
    flags = [] if unsafe else ["-Wall", "-Wextra", "-Werror"]
    use_ccache = False
    
    if fast:
        flags.append("-O0")
        use_ccache = has_ccache()
        cache_status = "ccache" if use_ccache else "no ccache"
        print(f"⚡ Fast mode: -O0, {cache_status}")
    
    # Detect build mode
    use_makefile = has_makefile(directory)
    
    if use_makefile:
        print("📦 Makefile mode (recursive watch)")
    else:
        print("🔧 Direct compilation mode")
    
    print("👀 Watching for changes... (Ctrl+C to stop)")
    print("-" * 40)
    
    # Initialize components
    watcher = FileWatcher(directory, recursive=use_makefile)
    compiler = CCompiler(flags, use_ccache)
    watcher.start()
    
    try:
        while True:
            clear_screen()
            
            if use_makefile:
                if compiler.make_build(directory):
                    interrupted = compiler.make_run(directory, watcher)
                    if interrupted:
                        print("\n🔄 File changed, recompiling...")
                        continue
            else:
                c_files = watcher.get_c_files()
                if c_files:
                    exe = compiler.compile_file(c_files[0])
                    if exe:
                        interrupted = compiler.run_file(exe, watcher)
                        if interrupted:
                            print("\n🔄 File changed, recompiling...")
                            continue
            
            # Wait for next file change
            watcher.wait_for_change()
            watcher.has_changed()  # Clear the flag
            
    except KeyboardInterrupt:
        print("\n👋 Stopping watcher...")
        compiler.kill()
        watcher.stop()


if __name__ == "__main__":
    main()
