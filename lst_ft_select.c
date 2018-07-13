/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_ft_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 12:41:25 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/25 14:05:43 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <stdlib.h>

void			ft_lst_selectdel(t_select *lst)
{
	while (lst != NULL)
		ft_lst_selectdelone(&lst, lst);
}

void			ft_lst_selectdelone(t_select **lst, t_select *node)
{
	*lst = node->next;
	free(node->name);
	node->name = NULL;
	node->stat = 0;
	node->line = 0;
	node->col = 0;
	node->next = NULL;
	node->prev = NULL;
	free(node);
	if ((*lst) != NULL && (*lst)->prev != NULL)
		(*lst)->prev->next = *lst;
}

t_select		*ft_lst_selectnew(void)
{
	t_select	*lst;

	if ((lst = (t_select *)malloc(sizeof(t_select))) == NULL)
		exit(EXIT_FAILURE);
	lst->line = 0;
	lst->col = 0;
	lst->stat = 0;
	lst->name = NULL;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

void			push_front_lst(t_linked_lst *lst, t_select *new)
{
	if (lst->head)
		lst->head->prev = new;
	new->next = lst->head;
	lst->head = new;
}

void			push_back_lst(t_linked_lst *lst, t_select *new)
{
	if (lst->tail)
		lst->tail->next = new;
	new->prev = lst->tail;
	lst->tail = new;
}
