/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_ft_select.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 13:00:49 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/29 15:21:24 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"
#include <term.h>

static void		interface_2(int sp, t_select *lst, float nb, int pos)
{
	pos = sp;
	while (sp-- > 0)
		ft_putchar('_');
	sp = pos;
	while (lst)
	{
		if (lst->stat == 2 || lst->stat == 3)
			nb += 0.001;
		if (lst->stat == 1 || lst->stat == 3)
			pos = (int)nb + 1;
		++nb;
		lst = lst->next;
	}
	tputs(tgoto(tgetstr("cm", NULL), (sp - 36) / 2, 9), 1, &ft_putchar_int);
	ft_putstr("Position: ");
	ft_putnbr(pos);
	ft_putstr(" / ");
	ft_putnbr((int)nb);
	ft_putstr(" | Selected: ");
	nb -= (int)nb;
	ft_putnbr((int)(nb * 1000));
	ft_putendl("\x1B[31m");
	while (sp-- > 0)
		ft_putchar('_');
	ft_putstr("\x1B[0m");
}

void			interface_ft_select(t_linked_lst *ln, int sp)
{
	if (ln->tp == 0 && ln->mode == 12)
	{
		tputs(tgoto(tgetstr("cm", NULL), sp, 0), 1, &ft_putchar_int);
		ft_putstr("\x1B[36m  __ _              _           _");
		tputs(tgoto(tgetstr("cm", NULL), sp, 1), 1, &ft_putchar_int);
		ft_putstr(" / _| |            | |         | |");
		tputs(tgoto(tgetstr("cm", NULL), sp, 2), 1, &ft_putchar_int);
		ft_putstr("| |_| |_   ___  ___| | ___  ___| |_");
		tputs(tgoto(tgetstr("cm", NULL), sp, 3), 1, &ft_putchar_int);
		ft_putstr("|  _| __| / __|/ _ \\ |/ _ \\/ __| __|");
		tputs(tgoto(tgetstr("cm", NULL), sp, 4), 1, &ft_putchar_int);
		ft_putstr("| | | |_  \\__ \\  __/ |  __/ (__| |_");
		tputs(tgoto(tgetstr("cm", NULL), sp, 5), 1, &ft_putchar_int);
		ft_putstr("|_|  \\__| |___/\\___|_|\\___|\\___|\\__|");
		tputs(tgoto(tgetstr("cm", NULL), sp + 7, 6), 1, &ft_putchar_int);
		ft_putstr("______");
		tputs(tgoto(tgetstr("cm", NULL), sp + 6, 7), 1, &ft_putchar_int);
		ft_putstr("|______|            \x1B[0mby rsibiet\n");
		interface_2(ln->c, ln->head, 0.0005, 0);
	}
	else if (ln->tp == 0)
	{
		ft_putendl("\x1B[36mft_select:\x1B[0m");
		ft_putendl("(Pocket mode)");
	}
}
