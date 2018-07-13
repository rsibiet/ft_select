/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen2_lst_select.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:08:10 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/24 15:21:07 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <unistd.h>
#include "libft.h"
#include <curses.h>
#include <term.h>

void			ft_select_up(t_select *lst, t_linked_lst *ln, int tp)
{
	while (lst && tp == 0)
	{
		if (lst->stat == 1 || lst->stat == 3)
		{
			if (lst->stat == 1)
				lst->stat = 0;
			else
				lst->stat = 2;
			if (lst->prev != NULL && lst->prev->stat == 0)
				lst->prev->stat = 1;
			else if (lst->prev != NULL && lst->prev->stat == 2)
				lst->prev->stat = 3;
			else if (lst->prev == NULL && ln->tail->stat == 0)
				ln->tail->stat = 1;
			else if (lst->prev == NULL && ln->tail->stat == 2)
				ln->tail->stat = 3;
			tp = 1;
		}
		lst = lst->next;
	}
	lst = ln->head;
}

void			ft_select_down(t_select *lst, t_linked_lst *ln, int tp)
{
	while (lst && tp == 0)
	{
		if (lst->stat == 1 || lst->stat == 3)
		{
			if (lst->stat == 1)
				lst->stat = 0;
			else
				lst->stat = 2;
			if (lst->next != NULL && lst->next->stat == 0)
				lst->next->stat = 1;
			else if (lst->next != NULL && lst->next->stat == 2)
				lst->next->stat = 3;
			else if (lst->next == NULL && ln->head->stat == 0)
				ln->head->stat = 1;
			else if (lst->next == NULL && ln->head->stat == 2)
				ln->head->stat = 3;
			tp = 1;
		}
		lst = lst->next;
	}
	lst = ln->head;
}

void			ft_select_select(t_select *lst, t_linked_lst *ln, int tp)
{
	while (lst && tp == 0)
	{
		if (lst->stat == 1 || lst->stat == 3)
		{
			if (lst->stat == 1)
				lst->stat = 2;
			else
				lst->stat = 0;
			if (lst->next != NULL && lst->next->stat == 0)
				lst->next->stat = 1;
			else if (lst->next != NULL && lst->next->stat == 2)
				lst->next->stat = 3;
			else if (ln->head->stat == 0)
				ln->head->stat = 1;
			else
				ln->head->stat = 3;
			tp = 1;
		}
		lst = lst->next;
	}
	lst = ln->head;
}

void			ft_return_select(t_select *lst, t_linked_lst *ln,
					int tp)
{
	tputs(tgetstr("cl", NULL), 0, &ft_putchar_int);
	while (lst)
	{
		if (tp == 1 && lst->stat >= 2)
			ft_putchar(' ');
		if (lst->stat >= 2)
		{
			tp = 1;
			ft_putstr(lst->name);
		}
		lst = lst->next;
	}
	if (tp == 1)
		ft_putchar('\n');
	lst = ln->head;
	exit_select(1, lst, NULL);
}

int				ft_putchar_int(int c)
{
	write(2, &c, 1);
	return (1);
}
