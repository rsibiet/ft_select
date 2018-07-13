/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 19:01:04 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/29 16:08:03 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <string.h>

typedef struct termios		t_term;
typedef struct stat			t_stat;
typedef struct dirent		t_dir;

/*
** stat => 0
**		   1 = curse on (souligne)
**		   2 = selected (videoinverse)
**		   3 = 1 + 2
** BONUS :
**	1. interface                          ok
**	2. ctrl_a                             ok
** 	3. display nb of elements			  ok
**	4. display nb of selected elements	  ok
**	5. display cursor position	 		  ok
**	6. reverse list with r                ok
**	7. color doc name					  ok
**  8. open / close doc                   ok
*/

typedef struct			s_pos
{
	int					col;
	int					line;
	size_t				max;
	int					i;
	int					nb;
	int					mem_col;
}						t_pos;

typedef struct			s_select
{
	int					line;
	int					col;
	int					stat;
	int					doc;
	char				*name;
	struct s_select		*next;
	struct s_select		*prev;
}						t_select;

typedef struct			s_linked_lst
{
	t_select			*head;
	t_select			*tail;
	int					tp;
	int					mode;
	int					l;
	int					c;
}						t_linked_lst;

/*
** Fonctions in main_ft_select file
*/

int						term_set(t_term *term);
void					exit_select(int tmp, t_select *lst, char *name);

/*
** Fonctions in lst_ft_select file
*/

void					ft_lst_selectdel(t_select *lst);
void					ft_lst_selectdelone(t_select **lst, t_select *node);
t_select				*ft_lst_selectnew(void);
void					push_front_lst(t_linked_lst *lst, t_select *new);
void					push_back_lst(t_linked_lst *lst, t_select *new);

/*
** Fonctions in gen_lst_select file
*/

void					ft_display_list(t_select *lst, t_linked_lst *ln);
void					ft_loop_select(t_linked_lst *ln);

/*
** Fonctions in gen2_lst_select file
*/

void					ft_select_up(t_select *lst, t_linked_lst *ln,
							int tp);
void					ft_select_down(t_select *lst, t_linked_lst *ln,
							int tp);
void					ft_select_select(t_select *lst, t_linked_lst *ln,
							int tp);
void					ft_return_select(t_select *lst, t_linked_lst *ln,
							int tp);
int						ft_putchar_int(int c);

/*
** Fonctions in gen3_lst_select file
*/

int						define_pos_node(t_select *lst, t_linked_lst *ln,
							t_pos pos);
void					ft_left_right(t_select *lst, t_linked_lst *ln,
							t_pos pos, int nb);

/*
** Fonctions in signal_ft_select file
*/

t_linked_lst			*ft_save_link(t_linked_lst *link, int i);
void					resize_ft_select(t_linked_lst *ln);
void					read_signal(int i);
void					ft_signal(void);

/*
** Fonctions in bonus_ft_select file
*/

void					bonus_ft_select(t_select *lst, t_linked_lst *ln,
							char c[3]);

/*
** Fonctions in interface_ft_select file
*/

void					interface_ft_select(t_linked_lst *ln, int sp);

#endif
