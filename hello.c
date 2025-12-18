/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:06:36 by danimend          #+#    #+#             */
/*   Updated: 2025/12/10 21:27:49 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "libft/libft.h"

typedef struct s_print_tmp
{
	void			*content;
	struct s_list	*next;
}	t_print_tmp;

static int	find_first_tag(const char *str, int skip)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && skip-- <= 0)
			return (i);
		i++;
	}
	return (-1);
}
#include <stdarg.h>

static void	write_unsigned_int(unsigned int number)
{
	char	number_as_char;

	if (number > 9)
	{
		number_as_char = '0' + (number % 10);
		write_unsigned_int(number / 10);
		write(0, &number_as_char, 1);
	}
	else
	{
		number_as_char = '0' + number;
		write(0, &number_as_char, 1);
	}
}

int sum_ints(int n, ...)
{
	va_list ap;
	va_start(ap, n);
	int sum = 0;
	for (int i = 0; i < n; ++i)
		sum += va_arg(ap, int);
	va_end(ap);
	return sum;
}

static int	process_tag(const char *tag) {
	return (0);
}

static int	count_tags(const char *str)
{
	int	count;

	count = 0;

	while (*str)
	{
		if (*str == '%')
			count++;

		str++;
	}

	return (count);
}

static void	write_hex(unsigned int number, int uppercase)
{
	static char	uppercase_base_16[] = "0123456789ABCDEF";
	static char	lowercase_base_16[] = "0123456789abcdef";

	if (number >= 16)
		write_hex(number / 16, uppercase);

	if (uppercase)
		write(0, &uppercase_base_16[number % 16], 1);
	else
		write(0, &lowercase_base_16[number % 16], 1);
}

// static void	print_to_idx(const char *str, int length)
// {
// 	write(1, str,
// }

void	ft_printf(char *str, ...)
{
	va_list	ap;
	int		tag_index;
	int		tag_count;

	tag_index = 0;
	va_start(ap, count_tags(str));
	while (*str && str)
	{
		tag_index = find_first_tag(str, 0);
		if (tag_index < 0)
		{
			if (*str)
				write(0, str, ft_strlen(str));
			break ;
		}

		write(0, str, tag_index);
		char tag_type = *(str + tag_index + 1);

		if (tag_type == 'd' || tag_type == 'i')
		{
			char *r = ft_itoa(va_arg(ap, int));
			write(0, r, ft_strlen(r));
			free(r);
		}
		if (tag_type == 'u')
		{
			write_unsigned_int(va_arg(ap, unsigned int));
		}
		else if (tag_type == 'c')
		{
			char c = (char)va_arg(ap, unsigned int);
			write(0, &c, 1);
		}
		else if (tag_type == 's')
		{
			char *s = va_arg(ap, char *);
			if (s)
				write(0, s, ft_strlen(s));
			else
				write(0, "(null)", 6);
		}
		else if (tag_type == '%')
		{
			write(0, "%", 1);
		}
		else if (tag_type == 'x')
		{
			unsigned int num = va_arg(ap, unsigned int);
			write_hex(num, 0);
		}
		else if (tag_type == 'X')
		{
			unsigned int num = va_arg(ap, unsigned int);
			write_hex(num, 1);
		}

		str += tag_index + 2;
	}
	va_end(ap);
}

int	main(void)
{

	ft_printf("hello world, i'm %d years old and I ate %d burgers\n", 5, 10);

	// test with %c (chars)
	ft_printf("Character test: %c %c %c\n", 'A', 'B', 'C');

	// test with %s (strings)
	ft_printf("String %% test: %s %s %sLOL\n", "Hello", "world", "!");

	// test with %u (unsigned integers)
	ft_printf("Unsigned int test: %u %u %u\n", 4294967295U, 0U, 123456789U);

	// test with %x and %X (hexadecimal)
	ft_printf("Hexadecimal test: %x %X %x\n", 255, 255, 125165);

	return (0);
}
