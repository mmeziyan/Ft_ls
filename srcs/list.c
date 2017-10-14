/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:53:52 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/09/24 19:53:55 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	list_c(t_list *list)
{
	list->totalb = 0;
	list->size = 0;
	list->begin = NULL;
	list->end = NULL;
}

void	list_clean(t_list *list)
{
	list->size = 0;
	while (list->begin)
	{
		list->begin->prev = NULL;
		mdestroy(&list->begin);
		list->begin = list->begin->next;
		if (list->begin)
			list->begin->prev->next = NULL;
	}
	list->begin = NULL;
	list->end = NULL;
}

void	mcreate(t_flst **new)
{
	(*new = (t_flst *)malloc(sizeof(t_flst))) ? *new : exit(3);
	(*new)->links = NULL;
	(*new)->prev = NULL;
	(*new)->next = NULL;
}

void	mdestroy(t_flst **destroy)
{
	free((*destroy)->path);
	free((*destroy)->date);
	free((*destroy)->grp);
	free((*destroy)->pwd);
	(*destroy)->name = NULL;
	(*destroy)->path = NULL;
	(*destroy)->date = NULL;
	(*destroy)->grp = NULL;
	(*destroy)->pwd = NULL;
	free(*destroy);
}

void	add_right(t_list *list, t_flst *new)
{
	list->size++;
	if (!list->begin)
	{
		list->end = new;
		list->begin = new;
	}
	else
	{
		list->end->next = new;
		new->prev = list->end;
		list->end = new;
	}
}
