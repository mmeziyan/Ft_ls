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

void	ft_putcolor(t_flst *prt)
{
	if (prt == NULL)
	{
		ft_putstr("\x1B[0m");
		return ;
	}
	prt->type == 'd' ? ft_putstr("\x1B[36;1m") : 0;
	prt->type == 'l' ? ft_putstr("\x1B[35m") : 0;
	prt->type == '-' ? ft_putstr("\x1B[0m") : 0;
	(prt->type == '-' && prt->right[2] == 'x') ? ft_putstr("\x1B[31m") : 0;
	prt->type == 'p' ? ft_putstr("\x1B[33m") : 0;
	prt->type == 'c' ? ft_putstr("\x1B[34;43m") : 0;
	prt->type == 'b' ? ft_putstr("\x1B[34:46m") : 0;
	prt->type == 's' ? ft_putstr("\x1B[32m") : 0;
}

void	print_opt_lgo(t_flst *prt, t_size upper)
{
	ft_putspace(upper.link - ft_nblen(prt->link));
	opt("t") ? ft_putchar(' ') : 0;
	ft_putnbr(prt->link);
	if (!opt("g"))
	{
		ft_putspace(upper.user - (prt->pwd ? ft_strlen(prt->pwd) : 0) + 1);
		prt->pwd ? ft_putstr(prt->pwd) : 1;
		ft_putspace(1);
	}
	if (!opt("o"))
		ft_putspace(upper.group - (prt->grp ? ft_strlen(prt->grp) : 0));
	(prt->grp && !opt("o")) ? my_printf("%s", 1, prt->grp) : 1;
	if (prt->type != 'c' && prt->type != 'b')
	{
		ft_putspace(upper.size - ft_nblen(prt->size) + 2);
		upper.min + upper.max < 20 ? ft_putspace(upper.min + upper.max) : 0;
		my_printf("%d %s ", 1, prt->size, prt->date);
	}
	if (prt->type == 'c' || prt->type == 'b')
	{
		ft_putspace(upper.max - ft_nblen(prt->max) + 2);
		my_printf("%d, ", 1, prt->max);
		ft_putspace(upper.size + upper.min - ft_nblen(prt->min) - 3);
		my_printf("%d %s ", 1, prt->min, prt->date);
	}
}

void	aff_file_params(t_flst *prt, t_size upper, int n)
{
	if (opt("A") && !opt("a") &&
		((ft_strcmp(prt->name, ".") == 0 || ft_strcmp(prt->name, "..") == 0)))
		return ;
	opt("lgo") ? my_printf("%c%s", 1, prt->type, prt->right) : 0;
	opt("lgo") ? print_opt_lgo(prt, upper) : 0;
	ft_putcolor(prt);
	(n == 1) ? ft_putstr(prt->name) : ft_putstr(prt->path);
	ft_putcolor(NULL);
	if (opt("F"))
	{
		prt->type == 'p' ? ft_putchar('|') : 1;
		prt->type == '-' && prt->right[2] == 'x' ? ft_putchar('*') : 0;
		prt->type == 'l' ? ft_putchar('@') : 1;
	}
	opt("Fp") && prt->type == 'd' ? ft_putchar('/') : 1;
	(prt->links && opt("lgo")) ? my_printf(" -> %s\n", 1, prt->links)
		: ft_putendl("");
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
		if ((rp->d_name[0] == '.' && (opt("a") || opt("A")))
			|| rp->d_name[0] != '.')
			repo(&folder, path, rp);
	closedir(opdir);
	upper = upsize(&folder);
	ptr = (opt("r") ? folder.end : folder.begin);
	(opt("log") && ptr) ? my_printf("total %d\n", 1, folder.totalb) : 1;
	while (ptr)
	{
		aff_file_params(ptr, upper, 1);
		ptr = (opt("r") ? ptr->prev : ptr->next);
	}
	opt("R") ? recursive(&folder) : 1;
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
