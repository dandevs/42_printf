/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:23:01 by danimend          #+#    #+#             */
/*   Updated: 2025/11/26 15:23:02 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*c_b;
	unsigned char	c_c;

	c_b = (unsigned char *)b;
	c_c = (unsigned char)c;
	while (len--)
		*c_b++ = c_c;
	return (b);
}
