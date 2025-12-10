/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:06:36 by danimend          #+#    #+#             */
/*   Updated: 2025/12/10 21:27:49 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "42_libft/libft.h"

static int	find_first_tag(char *str, int skip)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && skip-- <= 0)
			return (i);
		i++;
	}
	return (-1);
}

int	main(void)
{
	printf("%d", find_first_tag("hello %world but %why!!", 0));
	return (0);
}
