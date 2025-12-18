/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:22:44 by danimend          #+#    #+#             */
/*   Updated: 2025/11/26 15:22:44 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*memory;
	unsigned char	chr;

	memory = (unsigned char *)s;
	chr = (unsigned char)c;
	while (n--)
	{
		if (*memory == chr)
			return ((void *)memory);
		memory++;
	}
	return (NULL);
}
