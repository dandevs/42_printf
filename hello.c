/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:06:36 by danimend          #+#    #+#             */
/*   Updated: 2026/02/10 14:24:14 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
