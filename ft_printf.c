/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by danimend          #+#    #+#             */
/*   Updated: 2025/12/18 00:00:00 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft/libft.h"
#include "utilities/utilities.h"

static int	handle_format(char tag_type, va_list ap)
{
	if (tag_type == '%')
		return (handle_tag_percent());
	else if (tag_type == 'd')
		return (handle_tag_d(ap));
	else if (tag_type == 'i')
		return (handle_tag_i(ap));
	else if (tag_type == 'u')
		return (handle_tag_u(ap));
	else if (tag_type == 'c')
		return (handle_tag_c(ap));
	else if (tag_type == 's')
		return (handle_tag_s(ap));
	else if (tag_type == 'p')
		return (handle_tag_p(ap));
	else if (tag_type == 'x')
		return (handle_tag_x(ap));
	else if (tag_type == 'X')
		return (handle_tag_upper_x(ap));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		count;
	char	tag_type;

	count = 0;
	va_start(ap, str);
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != '%')
			i++;
		if (i > 0)
		{
			write(1, str, i);
			count += i;
		}
		if (!str[i])
			break ;
		tag_type = str[i + 1];
		count += handle_format(tag_type, ap);
		str += i + 2;
	}
	va_end(ap);
	return (count);
}
