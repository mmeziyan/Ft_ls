/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:53:52 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/09/24 19:53:55 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	file_type(t_stat stats)
{
	if (S_ISREG(stats.st_mode))
		return ('-');
	if (S_ISCHR(stats.st_mode))
		return ('c');
	if (S_ISBLK(stats.st_mode))
		return ('b');
	if (S_ISFIFO(stats.st_mode))
		return ('p');
	if (S_ISLNK(stats.st_mode))
		return ('l');
	if (S_ISSOCK(stats.st_mode))
		return ('s');
	if (S_ISDIR(stats.st_mode))
		return ('d');
	return (25);
}

void	repo(t_list *folder, char *path, t_dir *rep)
{
	t_flst	*tmp;
	char	*t;

	mcreate(&tmp);
	t = (path[ft_strlen(path) - 1] == '/') ? NULL :
		(path = ft_strjoin(path, "/"));
	tmp->path = ft_strjoin(path, rep->d_name);
	t ? free(path) : 1;
	tmp->name = ft_strdup(rep->d_name);
	if (infix(tmp, folder) == -1)
		return ;
	add_right(folder, tmp);
	(search_opt('t') == 1) ? place(folder, 't') : place(folder, 'a');
}

void	protection(t_flst *new, t_stat stats)
{
	new->right[0] = (stats.st_mode & S_IRUSR) ? 'r' : '-';
	new->right[1] = (stats.st_mode & S_IWUSR) ? 'w' : '-';
	new->right[2] = (stats.st_mode & S_IXUSR) ? 'x' : '-';
	if (stats.st_mode & S_ISUID)
		new->right[2] = (stats.st_mode & S_IXUSR) ? 's' : 'S';
	new->right[3] = (stats.st_mode & S_IRGRP) ? 'r' : '-';
	new->right[4] = (stats.st_mode & S_IWGRP) ? 'w' : '-';
	new->right[5] = (stats.st_mode & S_IXGRP) ? 'x' : '-';
	if (stats.st_mode & S_ISGID)
		new->right[5] = (stats.st_mode & S_IXGRP) ? 's' : 'S';
	new->right[6] = (stats.st_mode & S_IROTH) ? 'r' : '-';
	new->right[7] = (stats.st_mode & S_IWOTH) ? 'w' : '-';
	new->right[8] = (stats.st_mode & S_IXOTH) ? 'x' : '-';
	if (stats.st_mode & S_ISVTX)
		new->right[8] = (stats.st_mode & S_IXOTH) ? 't' : 'T';
	new->right[9] = '\0';
}

void	ft_date(t_flst *new, t_stat stats)
{
	char	*tmp;
	char	*tmp2;

	new->date = ft_strsub(ctime(&stats.st_mtime), 4, 7);
	tmp = new->date;
	if ((time(NULL) - stats.st_mtime) < 15552000 && time(NULL)
		> stats.st_mtime)
	{
		tmp2 = ft_strsub(ctime(&stats.st_mtime), 11, 5);
		new->date = ft_strjoin(tmp, tmp2);
	}
	else
	{
		tmp2 = ft_strsub(ctime(&stats.st_mtime), 19, 5);
		new->date = ft_strjoin(tmp, tmp2);
	}
	free(tmp);
	free(tmp2);
}

int		infix(t_flst *new, t_list *st)
{
	t_stat	sta;
	t_group	*grp;
	t_pwd	*pwd;

	new->name = ft_strdup(recup_name(new->path));
	lstat(new->path, &sta);
	if (S_ISLNK(sta.st_mode))
	{
		new->links = ft_strnew(1024);
		new->links[readlink(new->path, (new->links), 1024)] = '\0';
	}
	protection(new, sta);
	ft_date(new, sta);
	st->totalb += sta.st_blocks;
	new->link = sta.st_nlink;
	new->size = sta.st_size;
	new->mtime = sta.st_mtime;
	new->type = file_type(sta);
	pwd = getpwuid(sta.st_uid);
	grp = getgrgid(sta.st_gid);
	new->max = new->type == 'c' ? MAJOR((int)sta.st_rdev) : -1;
	new->min = new->type == 'c' ? MINOR((int)sta.st_rdev) : -1;
	new->pwd = pwd ? ft_strdup(pwd->pw_name) : ft_itoa(sta.st_uid);
	new->grp = grp ? ft_strdup(grp->gr_name) : ft_itoa(sta.st_gid);
	return (0);
}
