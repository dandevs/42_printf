*This project has been created as part of the 42 curriculum by danimend*

## Description

ft_printf emulates printf, built on top of libft and recently introduced variadic functions.

For example `ft_printf("Hello %d!", 42)` Will print `Hello 42!`

## Instructions

To compile, simply run the `make` command.

For quick testing: `make && cc -Wall -Wextra -Werror test.c libftprintf.a`

```c
#include <stddef.h>
#include <limits.h>
#include "ft_printf.h"

int	main(void)
{
	ft_printf("hello world, i'm %d years old and I ate %d burgers", 5, 10);
	ft_printf("Character test: %c %c %c\n", 'A', 'B', 'C');
	ft_printf("String %% test: %s %s %sLOL\n", "Hello", "world", "!");
	ft_printf("Unsigned int test: %u %u %u\n", 4294967295U, 0U, 123456789U);
	ft_printf("Hexadecimal test: %x %X %x\n", 255, 255, 125165);
	ft_printf("Pointer test: %p %p %p\n", (void *)0, (void *)255, (void *)NULL);
	ft_printf("Integer test: %i %i %i\n", INT_MIN, 42, INT_MAX);
	return (0);
}

```

##  Resources
* Good old google and man pages relating to `printf` and on about variadic usage.
* Earlier projects from piscine for printing things like hex

## Implementation

1. Iterate through the string via a simple counter `i` until we hit a `%` char or null.
2. Print characters with `write` up until the `%` char or null
3. We pass the character after `%` to `handle_format` which then chooses how to `write` the given variadic argument.
4. Increment the string by `i` and reset `i` to 0.
4. Repeat while string is not null