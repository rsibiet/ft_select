/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen3_lst_select.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 17:37:12 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/29 13:02:26 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"
#include <sys/stat.h>

static void		define_pos_node2(t_select *lst, t_linked_lst *ln, t_pos *pos,
					int tp)
{
	t_stat		s;

	pos->line = 0;
	while (lst && pos->col > 0 && ln->l > 0)
	{
		if (lst->doc != 2 && lst->doc != 3)
			lst->doc = 0;
		if (lstat(lst->name, &s) != -1 && S_ISDIR(s.st_mode) &&
			(s.st_mode & S_IXUSR))
			lst->doc = 1;
		if (pos->line < pos->nb - 1 && tp == 1 &&
			pos->line + ln->mode + 1 < ln->l)
			++pos->line;
		else if (tp == 1)
		{
			pos->line = 0;
			++pos->i;
		}
		if (pos->line + ln->mode + 1 <= ln->l)
			lst->line = pos->line;
		lst->col = pos->i * (pos->max + 5);
		lst = lst->next;
		tp = 1;
	}
}

int				define_pos_node(t_select *lst, t_linked_lst *ln, t_pos pos)
{
	while (lst)
	{
		if (ft_strlen(lst->name) > pos.max)
			pos.max = ft_strlen(lst->name);
		lst = lst->next;
		++pos.nb;
	}
	lst = ln->head;
	if ((pos.col = (ln->c + 5) / (pos.max + 5)) == 0)
	{
		ln->tp = -1;
		return (0);
	}
	define_pos_node2(lst, ln, &pos, 0);
	lst = ln->head;
	if (pos.col < pos.i + 1 && ln->mode == 3)
		ln->tp = -1;
	else if (pos.col < pos.i + 1)
	{
		ln->mode = 3;
		pos.i = 0;
		pos.nb = 0;
		pos.i = define_pos_node(lst, ln, pos);
	}
	return (pos.i);
}

static void		ft_left_right2(t_select **lst, t_linked_lst *ln,
						t_pos *p, int *nb)
{
	p->i = 1;
	if (*nb == 0)
		*lst = (*lst)->next;
	else
		*lst = (*lst)->prev;
	if (*lst == NULL)
		p->nb++;
	if (*lst == NULL && *nb == 0)
		*lst = ln->head;
	else if (*lst == NULL && *nb == 1)
		*lst = ln->tail;
	if (p->col != -1 && p->col != (*lst)->col && p->line == (*lst)->line
		&& (*lst)->stat == 0)
		(*lst)->stat = 1;
	else if (p->col != -1 && p->col != (*lst)->col &&
		p->line == (*lst)->line && (*lst)->stat == 2)
		(*lst)->stat = 3;
	else
		p->i = 0;
}

void			ft_left_right(t_select *lst, t_linked_lst *ln, t_pos p, int nb)
{
	t_select	*tp;

	tp = NULL;
	while (p.mem_col > 0 && p.i == 0 && p.nb < 3)
	{
		if (lst->stat == 1 || lst->stat == 3)
		{
			tp = lst;
			if (lst->stat == 1)
				lst->stat = 0;
			else
				lst->stat = 2;
			p.col = lst->col;
			p.line = lst->line;
		}
		ft_left_right2(&lst, ln, &p, &nb);
	}
	if (p.nb == 3)
	{
		if (tp->stat == 0)
			tp->stat = 1;
		else
			tp->stat = 3;
	}
	lst = ln->head;
}
