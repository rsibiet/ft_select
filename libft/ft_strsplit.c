/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 20:00:50 by rsibiet           #+#    #+#             */
/*   Updated: 2015/11/29 15:56:54 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		**ft_malloc_tab(char const *s, char c)
{
	char	**tab;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			k++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	tab = (char **)malloc(sizeof(char *) * (k + 1));
	if (tab == NULL)
		return (NULL);
	tab[k] = ft_strnew(0);
	tab[k] = NULL;
	return (tab);
}

static int		ft_push_i_and_j(char const *s, char c, int i, int *j)
{
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i + *j] != c && s[i + *j] != '\0')
		(*j)++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	int		memo_i;
	char	**tab;

	tab = ft_malloc_tab(s, c);
	i = 0;
	j = 0;
	k = 0;
	while (s[i] != '\0')
	{
		i = ft_push_i_and_j(s, c, i, &j);
		if (j != 0)
			tab[k] = ft_strnew(j);
		memo_i = i + j;
		while (j > 0)
		{
			j--;
			tab[k][j] = s[i + j];
		}
		i = memo_i;
		k++;
	}
	return (tab);
}
