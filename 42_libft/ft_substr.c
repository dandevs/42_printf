/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:23:56 by danimend          #+#    #+#             */
/*   Updated: 2025/11/26 15:23:56 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*result;
	char	*result_ptr;

	if (start > ft_strlen(s))
		len = 0;
	else if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	result = malloc(sizeof(char) * (len + 1));
	result_ptr = result;
	if (!result)
		return (NULL);
	while (start--)
	{
		if (!*s)
		{
			*result = '\0';
			return (result_ptr);
		}
		s++;
	}
	while (len-- && *s)
		*result++ = *s++;
	*result = '\0';
	return (result_ptr);
}
