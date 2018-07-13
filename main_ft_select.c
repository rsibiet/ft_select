/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 19:06:11 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/25 14:37:01 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>

void				exit_select(int tmp, t_select *lst, char *name)
{
	t_term		reset;

	tgetent(NULL, name);
	tcgetattr(0, &reset);
	reset.c_lflag |= (ICANON | ECHO);
	if (tmp != 1)
		tputs(tgetstr("cl", NULL), 0, &ft_putchar_int);
	tputs(tgetstr("ve", NULL), 0, &ft_putchar_int);
	tcsetattr(0, 0, &reset);
	if (tmp == -1)
		ft_putendl_fd("Requested changes failed.", 2);
	ft_lst_selectdel(lst);
	if (tmp >= 0)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

static t_linked_lst	ft_lst_selectinit(int ac, char **av, t_select *lst)
{
	t_linked_lst	link;
	t_select		*new;
	t_select		*prev;
	int				i;

	i = 1;
	link.tail = lst;
	lst->name = ft_strdup(av[1]);
	lst->stat = 1;
	lst->next = NULL;
	lst->prev = NULL;
	link.head = lst;
	link.tp = 0;
	new = lst;
	prev = NULL;
	while (i++ < ac - 1)
	{
		new->next = ft_lst_selectnew();
		push_back_lst(&link, new->next);
		new->prev = prev;
		prev = new;
		new = new->next;
		new->name = ft_strdup(av[i]);
	}
	return (link);
}

int					term_set(t_term *term)
{
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, term) == -1)
		return (-1);
	return (0);
}

static void			error_tgetent(int tmp, t_select *lst)
{
	if (tmp == -2)
	{
		ft_putendl_fd("\x1B[31mft_select: List empty.", 2);
		ft_putendl_fd("\x1B[37mft_select need argument(s).", 2);
	}
	else if (tmp == -1)
		ft_putendl_fd("TERM variable not found.", 2);
	if (tmp == 1)
		ft_putendl_fd("Could not access the termcap data base.", 2);
	else if (tmp == 2)
		ft_putendl_fd("Storage of parameters in termios structure failed", 2);
	if (tmp != -2)
		ft_lst_selectdel(lst);
	exit(EXIT_FAILURE);
}

int					main(int ac, char **av)
{
	char			*name_term;
	t_term			term;
	t_select		*lst;
	t_linked_lst	link;

	name_term = NULL;
	lst = NULL;
	if (ac == 1)
		error_tgetent(-2, lst);
	lst = ft_lst_selectnew();
	link = ft_lst_selectinit(ac, av, lst);
	ft_save_link(&link, 0);
	if ((name_term = getenv("TERM")) == NULL)
		error_tgetent(-1, lst);
	if (tgetent(NULL, name_term) == -1)
		error_tgetent(1, lst);
	if (tcgetattr(0, &term) == -1)
		error_tgetent(2, lst);
	if (term_set(&term) == -1)
		exit_select(-1, lst, NULL);
	ft_signal();
	ft_loop_select(&link);
	return (0);
}
