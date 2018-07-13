/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_ft_select.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:19:24 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/29 15:39:24 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <signal.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>
#include <stdlib.h>

t_linked_lst	*ft_save_link(t_linked_lst *ln, int i)
{
	static t_linked_lst		*tmp = NULL;

	if (i == 0)
		tmp = ln;
	return (tmp);
}

void			resize_ft_select(t_linked_lst *link)
{
	struct winsize	ws;
	t_pos			pos;

	pos.line = 0;
	pos.max = 0;
	pos.i = 0;
	pos.nb = 0;
	link = ft_save_link(NULL, 1);
	ioctl(0, TIOCGWINSZ, &ws);
	link->l = ws.ws_row;
	link->c = ws.ws_col;
	tputs(tgetstr("vi", NULL), 1, &ft_putchar_int);
	tputs(tgetstr("cl", NULL), 1, &ft_putchar_int);
	link->mode = 3;
	if (link->c >= 36)
		link->mode = 12;
	define_pos_node(link->head, link, pos);
	interface_ft_select(link, (link->c - 36) / 2);
	ft_display_list(link->head, link);
}

static void		ctrl_z_ft_select(char *name_t, int i)
{
	char				c[2];
	t_term				memo_t;

	name_t = getenv("TERM");
	tgetent(NULL, name_t);
	tcgetattr(0, &memo_t);
	tputs(tgetstr("cl", NULL), 1, &ft_putchar_int);
	if (i == SIGTSTP)
	{
		c[0] = memo_t.c_cc[VSUSP];
		c[1] = 0;
		memo_t.c_lflag |= (ICANON | ECHO);
		tputs(tgetstr("ve", NULL), 1, &ft_putchar_int);
		tcsetattr(0, 0, &memo_t);
		ioctl(0, TIOCSTI, c);
		signal(SIGTSTP, SIG_DFL);
	}
	else
	{
		term_set(&memo_t);
		signal(SIGTSTP, read_signal);
		resize_ft_select(NULL);
	}
}

void			read_signal(int i)
{
	if (i == SIGWINCH)
		resize_ft_select(NULL);
	else if (i == SIGTSTP || i == SIGCONT)
		ctrl_z_ft_select(NULL, i);
	else
		exit_select(0, (ft_save_link(NULL, 1))->head, NULL);
}

void			ft_signal(void)
{
	int		i;

	i = 1;
	while (i < 32)
	{
		signal(i, read_signal);
		i++;
	}
}
