/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:53:52 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/09/24 19:53:55 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_sort_params(char **tab)
{
	long int	*nbtab;
	t_stat		stats;
	int			i;

	i = ft_tabtool(tab, "len");
	nbtab = malloc(sizeof(long int) * i);
	i = 0;
	while (tab[i])
	{
		stat(tab[i], &stats);
		nbtab[i] = stats.st_mtime;
		i++;
	}
	i = -1;
	search_opt('t') ? ft_tab_sort2(tab, nbtab, 0) : 1;
	search_opt('r') ? ft_tab_rev(&tab, 0) : 1;
	print_params(tab);
}

void	place(t_list *list, unsigned char mode)
{
	t_flst *tmp;

	tmp = list->end;
	if (mode == 'a')
		while (tmp->prev && ft_strcmp(tmp->name, tmp->prev->name) < 0)
			move_left(list, tmp);
	if (mode == 't')
	{
		while (tmp->prev && tmp->mtime > tmp->prev->mtime)
			move_left(list, tmp);
		while (tmp->prev && tmp->mtime == tmp->prev->mtime && \
			ft_strcmp(tmp->name, tmp->prev->name) < 0)
			move_left(list, tmp);
	}
}

int		move_left(t_list *list, t_flst *mv)
{
	t_flst	*ptrn;
	t_flst	*ptrp;
	t_flst	*ptrpp;

	if (mv->prev)
	{
		ptrpp = mv->prev->prev ? mv->prev->prev : NULL;
		ptrn = mv->next;
		ptrp = mv->prev;
		list->begin = ptrpp ? list->begin : mv;
		list->end = ptrn ? list->end : ptrp;
		ptrp->next = ptrn ? ptrn : NULL;
		mv->next = ptrp;
		mv->prev = ptrpp ? ptrpp : NULL;
		ptrp->prev = mv;
		if (ptrpp)
			ptrpp->next = mv;
		if (ptrn)
			ptrn->prev = ptrp;
		return (1);
	}
	return (0);
}
