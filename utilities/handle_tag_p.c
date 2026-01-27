/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tag_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by danimend          #+#    #+#             */
/*   Updated: 2025/12/18 00:00:00 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

static int	write_pointer_number(unsigned long nb, char *base, int base_len)
{
	char	c;
	int		count;

	count = 0;
	if (nb >= (unsigned long)base_len)
		count += write_pointer_number(nb / base_len, base, base_len);
	c = base[nb % base_len];
	write(1, &c, 1);
	return (count + 1);
}

int	handle_tag_p(va_list ap)
{
	unsigned long	ptr;
	int				count;

	ptr = va_arg(ap, unsigned long);
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	count = 0;
	write(1, "0x", 2);
	count += 2;
	count += write_pointer_number(ptr, "0123456789abcdef", 16);
	return (count);
}
