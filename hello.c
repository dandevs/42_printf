/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:06:36 by danimend          #+#    #+#             */
/*   Updated: 2025/12/10 20:42:03 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "42_libft/libft.h"

static int	find_first_tag(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '%')
		i++;
	return (i);
}

int	main(void)
{
	printf("Hello what d\n");
	printf("What!\n");
	return (0);
}
