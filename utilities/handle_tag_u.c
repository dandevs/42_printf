/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tag_u.c                                     :+:      :+:    :+:   */
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

int	handle_tag_u(va_list ap)
{
	return (write_number(va_arg(ap, unsigned int), "0123456789", 10));
}
