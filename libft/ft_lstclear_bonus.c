/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:22:26 by danimend          #+#    #+#             */
/*   Updated: 2025/11/26 15:22:26 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp_next;

	if (!lst || *lst == NULL)
		return ;
	while (*lst)
	{
		tmp_next = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp_next;
	}
}
