/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:22:15 by danimend          #+#    #+#             */
/*   Updated: 2025/12/09 14:42:38 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*zero_str(void)
{
	char	*a;

	a = malloc(sizeof(char) * 2);
	if (!a)
		return (NULL);
	a[0] = '0';
	a[1] = '\0';
	if (!a)
		return (NULL);
	return (a);
}

static void	make_negative(unsigned int *v, int *j, int n)
{
	*v = (unsigned int)(-n);
	(*j)++;
}

static void	create_tmp_arr(char *tmp, int *i, unsigned int *v)
{
	while (*v > 0)
	{
		tmp[(*i)++] = '0' + (*v % 10);
		*v /= 10;
	}
}

char	*ft_itoa(int n)
{
	char			tmp[16];
	char			*a;
	int				i;
	int				j;
	unsigned int	v;

	if (n == 0)
		return (zero_str());
	v = n;
	j = 0;
	i = 0;
	if (n < 0)
		make_negative(&v, &j, n);
	create_tmp_arr(tmp, &i, &v);
	a = malloc(sizeof(char) * (i + 1 + j));
	if (!a)
		return (NULL);
	while (i)
		a[j++] = tmp[--i];
	if (n < 0)
		a[0] = '-';
	a[j] = '\0';
	return (a);
}
