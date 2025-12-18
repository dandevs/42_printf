/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tag_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by danimend          #+#    #+#             */
/*   Updated: 2025/12/18 00:00:00 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"

int	handle_tag_d(va_list ap)
{
	char	*r;
	int		len;

	r = ft_itoa(va_arg(ap, int));
	len = ft_strlen(r);
	write(1, r, len);
	free(r);
	return (len);
}
