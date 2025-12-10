import os
import time
import subprocess
import sys

def get_c_files_recursive(directory):
    """Get all .c files recursively from directory."""
    c_files = []
    for root, dirs, files in os.walk(directory):
        # Skip hidden directories like .git
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        for f in files:
            if f.endswith('.c'):
                c_files.append(os.path.join(root, f))
    return c_files

def get_c_files(directory):
    """Get .c files from a single directory (non-recursive)."""
    return [f for f in os.listdir(directory) if f.endswith('.c')]

def has_makefile(directory):
    """Check if a Makefile exists in the directory."""
    makefile_path = os.path.join(directory, "Makefile")
    return os.path.exists(makefile_path)

def make_and_run(directory, flags=None):
    """Build using make and run the executable."""
    if flags is None:
        flags = []
    
    # Clean and rebuild
    try:
        subprocess.run(["make", "fclean"], cwd=directory, check=False, 
                      capture_output=True)
        result = subprocess.run(["make"], cwd=directory, check=True,
                              capture_output=True)
    except subprocess.CalledProcessError:
        return
    
    # Clear terminal after compilation
    os.system('clear')
    
    # Run using make run target
    try:
        subprocess.run(["make", "run"], cwd=directory, check=False)
    except Exception:
        pass

def compile_and_run(filepath, flags=None):
    """Compile a single file and run it."""
    if flags is None:
        flags = []
    # Determine executable name (remove .c extension)
    exe_name = os.path.splitext(filepath)[0]
    
    # Compile
    compile_cmd = ["cc"] + flags + [filepath, "-o", exe_name]
    try:
        # We don't capture output so it flows to stdout/stderr
        subprocess.run(compile_cmd, check=True)
    except subprocess.CalledProcessError:
        return

    # Clear terminal
    os.system('clear')

    # Run
    run_cmd = [f"./{exe_name}"]
    try:
        subprocess.run(run_cmd, check=False)
    except Exception:
        pass
    
    # Delete executable
    if os.path.exists(exe_name):
        try:
            os.remove(exe_name)
        except OSError:
            pass

def main():
    directory = "."
    unsafe = False
    
    # Parse arguments
    args = sys.argv[1:]
    if "--unsafe" in args:
        unsafe = True
        args.remove("--unsafe")
        
    if args:
        directory = args[0]

    flags = ["-Wall", "-Wextra", "-Werror"] if not unsafe else []

    # Check if we should use Makefile mode
    use_makefile = has_makefile(directory)
    
    if use_makefile:
        print("📦 Makefile detected - using make to build")
        print("👀 Watching .c files recursively...")
        print("-" * 40)
    else:
        print("🔧 No Makefile - using direct compilation")
        print("👀 Watching .c files in current directory...")
        print("-" * 40)

    # Map: filepath -> mtime
    mtimes = {}

    # Initialize mtimes and do initial build
    try:
        if use_makefile:
            c_files = get_c_files_recursive(directory)
            for filepath in c_files:
                mtimes[filepath] = os.path.getmtime(filepath)
            # Initial build
            make_and_run(directory, flags)
        else:
            for f in get_c_files(directory):
                filepath = os.path.join(directory, f)
                mtimes[filepath] = os.path.getmtime(filepath)
                compile_and_run(filepath, flags)
    except OSError:
        pass

    try:
        while True:
            time.sleep(1)
            try:
                if use_makefile:
                    current_files = get_c_files_recursive(directory)
                else:
                    current_files = [os.path.join(directory, f) 
                                    for f in get_c_files(directory)]
            except OSError:
                continue
            
            changed = False
            for filepath in current_files:
                try:
                    current_mtime = os.path.getmtime(filepath)
                    
                    if filepath not in mtimes:
                        # New file found, start tracking
                        mtimes[filepath] = current_mtime
                        changed = True
                    elif current_mtime != mtimes[filepath]:
                        mtimes[filepath] = current_mtime
                        changed = True
                except OSError:
                    continue
            
            if changed:
                if use_makefile:
                    make_and_run(directory, flags)
                else:
                    # In non-makefile mode, compile the changed file
                    for filepath in current_files:
                        if filepath in mtimes:
                            compile_and_run(filepath, flags)
                            break
                    
    except KeyboardInterrupt:
        pass

if __name__ == "__main__":
    main()
