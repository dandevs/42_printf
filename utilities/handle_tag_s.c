/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tag_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by danimend          #+#    #+#             */
/*   Updated: 2025/12/18 00:00:00 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "../libft/libft.h"

int	handle_tag_s(va_list ap)
{
	char	*s;
	int		len;

	s = va_arg(ap, char *);
	if (s)
	{
		len = ft_strlen(s);
		write(1, s, len);
		return (len);
	}
	else
	{
		write(1, "(null)", 6);
		return (6);
	}
}
