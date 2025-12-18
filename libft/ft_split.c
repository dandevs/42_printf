/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:23:17 by danimend          #+#    #+#             */
/*   Updated: 2025/12/09 15:11:24 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	append_to_arr(char ***arr_ptr, char *str)
{
	int		i;
	char	**arr;
	char	**new_arr;

	arr = *arr_ptr;
	i = 0;
	while (arr && arr[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (0);
	i = 0;
	while (arr[i])
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = str;
	new_arr[i + 1] = NULL;
	free(arr);
	*arr_ptr = new_arr;
	return (1);
}

static int	create_and_append(char ***arr_ptr, const char *s, size_t len)
{
	char	*to_append;
	size_t	j;

	to_append = malloc(sizeof(char) * (len + 1));
	if (!to_append)
		return (0);
	j = 0;
	while (j < len)
	{
		to_append[j] = s[j];
		j++;
	}
	to_append[j] = '\0';
	if (append_to_arr(arr_ptr, to_append))
		return (1);
	else
	{
		free(to_append);
		return (0);
	}
}

static void	iterate(const char **s, size_t *i, char c)
{
	const char	*p = *s;

	while (*p && *p == c)
		p++;
	while (p[*i] && p[*i] != c)
		(*i)++;
	*s = p;
}

static char	**empty_arry(void)
{
	char	**arr;

	arr = malloc(sizeof(char *));
	if (!arr)
		return (NULL);
	arr[0] = NULL;
	return (arr);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	i;

	arr = empty_arry();
	if (!arr)
		return (NULL);
	while (*s)
	{
		i = 0;
		iterate(&s, &i, c);
		if (i > 0)
		{
			if (!create_and_append(&arr, s, i))
			{
				i = 0;
				while (arr[i])
					free(arr[i++]);
				free(arr);
				return (NULL);
			}
		}
		s += i;
	}
	return (arr);
}
