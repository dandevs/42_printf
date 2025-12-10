/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:23:34 by danimend          #+#    #+#             */
/*   Updated: 2025/11/26 15:23:34 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	dst += dst_len;
	if (size <= 0 || size <= dst_len)
		return (src_len + size);
	while (i < size - dst_len - 1 && src[i])
	{
		*dst = src[i];
		dst++;
		i++;
	}
	*dst = '\0';
	return (dst_len + src_len);
}
