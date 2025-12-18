/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:22:54 by danimend          #+#    #+#             */
/*   Updated: 2025/11/26 15:22:55 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*c_dst;
	char	*c_src;

	if (!src && !dst)
		return (NULL);
	c_dst = (char *)dst;
	c_src = (char *)src;
	if (c_src < c_dst)
	{
		while (len--)
			c_dst[len] = c_src[len];
	}
	else
	{
		while (len--)
			*c_dst++ = *c_src++;
	}
	return (dst);
}
