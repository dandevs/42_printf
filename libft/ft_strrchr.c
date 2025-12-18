/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:23:51 by danimend          #+#    #+#             */
/*   Updated: 2025/11/26 15:23:51 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int character)
{
	char	*found_char;

	found_char = NULL;
	while (*str)
	{
		if (*str == (unsigned char)character)
			found_char = (char *)str;
		str++;
	}
	if (*str == (unsigned char)character)
		return ((char *)str);
	return (found_char);
}
