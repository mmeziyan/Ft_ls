/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:53:52 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/09/24 19:53:55 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_params(char **tab)
{
	t_list	params;
	t_flst	*file;
	t_size	upper;
	t_flst	*tmp;
	int		i;

	list_c(&params);
	file = NULL;
	i = -1;
	while (tab[++i])
	{
		mcreate(&file);
		file->path = ft_strdup(tab[i]);
		infix(file, &params) == -1 ? 1 : add_right(&params, file);
	}
	upper = upsize(&params);
	tmp = params.begin;
	while (tmp)
	{
		(tmp->type == 'd') ? i = -7 : aff_file_params(tmp, upper, 0);
		tmp = tmp->next;
	}
	if (i == -7)
		print_repo(&params);
}

char	**clean_av(char **av, int i)
{
	t_stat	st;
	char	**new;
	int		n;
	int		x;

	n = 0;
	x = i - 1;
	ft_tab_sort(av, i);
	while (av[++x])
		if (lstat(av[x], &st) == 0)
			n++;
	new = malloc(sizeof(char *) * (n + 1));
	new[n] = NULL;
	x = 0;
	while (av[i])
	{
		n = lstat(av[i], &st);
		new = n == 0 ? av[i] : NULL;
		(n != 0) ?
			my_printf("ls: %s: No such file or directory\n", 2, av[i]) : 0;
		new[x] == NULL ? 0 : x++;
		i++;
	}
	return (new);
}
