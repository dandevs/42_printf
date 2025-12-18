/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:23:54 by danimend          #+#    #+#             */
/*   Updated: 2025/12/09 14:35:10 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	contains_from_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static char	*empty_string(void)
{
	char	*str;

	str = malloc(sizeof(char) * 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	size_t		i;
	size_t		diff;
	char		*trimmed;

	if (!s1 || !set || !*s1)
		return (empty_string());
	i = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && contains_from_set(s1[start], set))
		start++;
	while (end > start && s1[end] && contains_from_set(s1[end], set))
		end--;
	end++;
	diff = end - start;
	trimmed = malloc(sizeof(char) * (diff + 1));
	if (!trimmed)
		return (NULL);
	while (i < diff)
		trimmed[i++] = s1[start++];
	trimmed[i] = '\0';
	return (trimmed);
}
