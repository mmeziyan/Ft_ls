/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:53:52 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/09/24 19:53:55 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_putspace(int n)
{
	while (n-- > 0)
	{
		ft_putchar(' ');
	}
}

void	aff_file_params(t_flst *prt, t_size upper, int n)
{
	if (search_opt('l'))
	{
		my_printf("%c%s", 1, prt->type, prt->right);
		ft_putspace(upper.link - ft_nblen(prt->link) + 1);
		ft_putnbr(prt->link);
		ft_putspace(upper.user - (prt->pwd ? ft_strlen(prt->pwd) : 0) + 1);
		prt->pwd ? ft_putstr(prt->pwd) : 1;
		ft_putspace(upper.group - (prt->grp ? ft_strlen(prt->grp) : 0) + 1);
		prt->grp ? my_printf("%s", 1, prt->grp) : 1;
		if (prt->type != 'c')
		{
			ft_putspace(upper.size - ft_nblen(prt->size) + 1);
			if (upper.min + upper.max < 20)
				ft_putspace(upper.min + upper.max);
			my_printf("%d %s ", 1, prt->size, prt->date);
		}
		if (prt->type == 'c')
		{
			ft_putspace(upper.max - ft_nblen(prt->max) + 2);
			my_printf("%d, ", 1, prt->max);
			ft_putspace(upper.size + upper.min - ft_nblen(prt->min) - 3);
			my_printf("%d %s ", 1, prt->min, prt->date);
		}
	}
	(n == 1) ? ft_putstr(prt->name) : ft_putstr(prt->path);
	(prt->links && search_opt('l')) ? my_printf(" -> %s\n",
		1, prt->links) : ft_putendl("");
}

void	print_folder(char *path)
{
	DIR		*opdir;
	t_list	folder;
	t_dir	*rp;
	t_flst	*ptr;
	t_size	upper;

	list_c(&folder);
	opdir = opendir(path);
	opdir ? 1 : my_printf("ls: %s: %s\n", 2, recup_name(path), strerror(errno));
	if (!opdir)
		return ;
	while ((rp = readdir(opdir)))
		if ((rp->d_name[0] == '.' && search_opt('a')) || rp->d_name[0] != '.')
			repo(&folder, path, rp);
	closedir(opdir);
	upper = upsize(&folder);
	ptr = (search_opt('r') ? folder.end : folder.begin);
	(search_opt('l') && ptr) ? my_printf("total %d\n", 1, folder.totalb) : 1;
	while (ptr)
	{
		aff_file_params(ptr, upper, 1);
		ptr = (search_opt('r') ? ptr->prev : ptr->next);
	}
	search_opt('R') ? recursive(&folder) : 1;
}

void	print_repo(t_list *params)
{
	t_flst	*tmp;
	int		n;

	n = 0;
	tmp = params->begin;
	while (tmp)
	{
		tmp->type != 'd' ? (n = 1) : 1;
		tmp = tmp->next;
	}
	tmp = params->begin;
	while (tmp)
	{
		while (tmp->type != 'd')
			if (!(tmp = tmp->next))
				return ;
		n ? ft_putchar('\n') : (n = 1);
		(arg_nbr() != 1) ? my_printf("%s:\n", 1, tmp->path) : 1;
		print_folder(tmp->path);
		tmp = tmp->next;
	}
}

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
