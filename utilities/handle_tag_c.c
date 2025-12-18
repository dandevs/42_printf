/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tag_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by danimend          #+#    #+#             */
/*   Updated: 2025/12/18 00:00:00 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int	handle_tag_c(va_list ap)
{
	char	c;

	c = (char)va_arg(ap, unsigned int);
	write(1, &c, 1);
	return (1);
}
