/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_lst_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 19:30:08 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/29 15:21:45 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>

void			ft_display_list(t_select *lst, t_linked_lst *ln)
{
	t_select		*cur;

	cur = lst;
	while (cur && ln->tp != -1)
	{
		if (cur->stat == 1 || cur->stat == 3)
			tputs(tgetstr("us", NULL), 1, &ft_putchar_int);
		if (cur->stat == 2 || cur->stat == 3)
			tputs(tgetstr("mr", NULL), 1, &ft_putchar_int);
		if (cur->doc == 1 || cur->doc == 3)
			ft_putstr("\x1B[32m");
		if (cur->doc == 2)
			ft_putstr("\x1B[33m");
		tputs(tgoto(tgetstr("cm", NULL), cur->col, cur->line + ln->mode), 1,
			&ft_putchar_int);
		ft_putstr(cur->name);
		tputs(tgetstr("ue", NULL), 1, &ft_putchar_int);
		tputs(tgetstr("me", NULL), 1, &ft_putchar_int);
		cur = cur->next;
	}
	ln->tp = 0;
}

static void		ft_del_select(t_select *lst)
{
	if (lst->next->stat == 2)
		lst->next->stat = 3;
	else
		lst->next->stat = 1;
	lst->next->prev = lst->prev;
}

static void		ft_delete_select(t_select *lst, t_linked_lst *ln, int tp)
{
	while (lst && tp == 0)
	{
		if (lst->stat == 1 || lst->stat == 3)
		{
			if (lst->prev != NULL)
				lst->prev->next = lst->next;
			if (lst->next != NULL)
				ft_del_select(lst);
			else if (ln->head->stat == 0)
				ln->head->stat = 1;
			else
				ln->head->stat = 3;
			if (ln->head == lst)
				ln->head = lst->next;
			if (ln->tail == lst)
				ln->tail = lst->prev;
			ft_lst_selectdelone(&lst, lst);
			tp = 1;
		}
		else
			lst = lst->next;
	}
}

static void		ft_move_cursor(t_select **lst, t_linked_lst *ln,
					t_pos *pos)
{
	char			c[3];

	pos->col = -1;
	read(0, c, 3);
	if (c[0] == '\033' && c[1] == '[')
	{
		if (c[2] == 'A')
			ft_select_up(*lst, ln, 0);
		else if (c[2] == 'B')
			ft_select_down(*lst, ln, 0);
		else if (c[2] == 'C')
			ft_left_right(*lst, ln, *pos, 0);
		else if (c[2] == 'D')
			ft_left_right(*lst, ln, *pos, 1);
	}
	else if ((c[0] == '\177' || c[0] == '\010') && c[1] == 0)
		ft_delete_select(*lst, ln, 0);
	else if (c[0] == '\012' && c[1] == 0)
		ft_return_select(*lst, ln, 0);
	else if (c[0] == '\040' && c[1] == 0)
		ft_select_select(*lst, ln, 0);
	else
		bonus_ft_select(*lst, ln, c);
	if (*lst == NULL || (c[0] == '\033' && c[1] == 0))
		exit_select(0, *lst, NULL);
}

void			ft_loop_select(t_linked_lst *ln)
{
	t_pos				pos;
	struct winsize		ws;

	pos.line = 0;
	pos.max = 0;
	pos.i = 0;
	pos.nb = 0;
	tputs(tgetstr("vi", NULL), 1, &ft_putchar_int);
	ioctl(0, TIOCGWINSZ, &ws);
	ln->l = ws.ws_row;
	ln->c = ws.ws_col;
	while (1)
	{
		tputs(tgetstr("cl", NULL), 1, &ft_putchar_int);
		pos.col = 0;
		ln->mode = 3;
		if (ln->c >= 36)
			ln->mode = 12;
		pos.mem_col = define_pos_node(ln->head, ln, pos);
		interface_ft_select(ln, (ln->c - 36) / 2);
		ft_display_list(ln->head, ln);
		ft_move_cursor(&ln->head, ln, &pos);
	}
}
