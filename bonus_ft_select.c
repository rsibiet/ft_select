/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_ft_select.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 17:08:08 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/25 17:04:23 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <curses.h>
#include <term.h>
#include <dirent.h>
#include "libft.h"

static void		open_doc(t_linked_lst *ln, t_select *lst, t_select *tp,
		DIR *doc)
{
	t_dir		*file;
	char		*c;
	t_select	*new;

	c = ft_strjoin(lst->name, " /");
	ft_strdel(&lst->name);
	lst->name = c;
	while ((file = readdir(doc)) != NULL)
	{
		if (file->d_name[0] != '.')
		{
			new = ft_lst_selectnew();
			lst->next = new;
			new->name = ft_strjoin(" ", file->d_name);
			new->doc = 2;
			new->prev = lst;
			lst = new;
		}
	}
	lst->next = tp;
	if (tp != NULL)
		tp->prev = lst;
	else
		ln->tail = lst;
	closedir(doc);
}

static void		close_doc(t_linked_lst *ln, t_select *lst, t_select *tp,
					size_t i)
{
	char	*c;

	i = ft_strlen(lst->name);
	c = ft_strsub(lst->name, 0, i - 2);
	ft_strdel(&lst->name);
	lst->name = c;
	while (tp != NULL && tp->doc == 2)
		ft_lst_selectdelone(&tp, tp);
	lst->next = tp;
	if (tp != NULL)
		tp->prev = lst;
	else
		ln->tail = lst;
}

static void		open_doc_selected(t_select *lst, t_linked_lst *ln)
{
	DIR		*doc;

	doc = NULL;
	while (lst)
	{
		if (lst->stat == 1 || lst->stat == 3)
		{
			if (lst->doc == 1)
			{
				lst->doc = 3;
				doc = opendir(lst->name);
				open_doc(ln, lst, lst->next, doc);
			}
			else if (lst->doc == 3)
			{
				lst->doc = 1;
				close_doc(ln, lst, lst->next, 0);
			}
		}
		lst = lst->next;
	}
}

static void		reverse_ft_select(t_select *ctrl, t_select *lst,
					t_linked_lst *ln, char c[3])
{
	t_select		*tp;

	while (ctrl)
	{
		if (ctrl->doc == 2)
			c[1] = 1;
		ctrl = ctrl->next;
	}
	if (c[0] == 'r' && c[1] != 1)
	{
		lst = ln->tail;
		tp = ln->tail;
		ln->tail = ln->head;
		ln->head = tp;
		while (tp != NULL)
		{
			tp = lst->prev;
			lst->prev = lst->next;
			lst->next = tp;
			lst = lst->next;
		}
		resize_ft_select(ln);
	}
	else if (c[0] == 9)
		open_doc_selected(lst, ln);
}

void			bonus_ft_select(t_select *lst, t_linked_lst *ln, char c[3])
{
	if ((c[0] == 'r' || c[0] == 9) && c[1] == 0)
		reverse_ft_select(lst, lst, ln, c);
	else if (c[0] == 1 && c[1] == 0)
	{
		while (lst)
		{
			if (lst->stat < 2)
				c[2] = 1;
			lst = lst->next;
		}
		lst = ln->head;
		while (lst)
		{
			if (lst->stat == 0 && c[2] == 1)
				lst->stat = 2;
			else if (lst->stat == 1 && c[2] == 1)
				lst->stat = 3;
			else if (lst->stat == 2 && c[2] != 1)
				lst->stat = 0;
			else if (lst->stat == 3 && c[2] != 1)
				lst->stat = 1;
			lst = lst->next;
		}
	}
}
