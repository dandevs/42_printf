/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tag_upper_x.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by danimend          #+#    #+#             */
/*   Updated: 2025/12/18 00:00:00 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

static int	write_number(unsigned int nb, char *base, int base_len)
{
	char	c;
	int		count;

	count = 0;
	if (nb >= (unsigned int)base_len)
		count += write_number(nb / base_len, base, base_len);
	c = base[nb % base_len];
	write(1, &c, 1);
	return (count + 1);
}

int	handle_tag_upper_x(va_list ap)
{
	unsigned int	num;

	num = va_arg(ap, unsigned int);
	return (write_number(num, "0123456789ABCDEF", 16));
}
