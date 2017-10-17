/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 00:32:48 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/02/21 18:50:54 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <string.h>
# include <sys/acl.h>
# include <sys/xattr.h>

# define MAJOR(x)((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x)((int32_t)((x) & 0xffffff))

typedef struct passwd	t_pwd;
typedef struct dirent	t_dir;
typedef struct stat		t_stat;
typedef struct group	t_group;
typedef struct time_t	t_time;

typedef struct			s_flst
{
	struct s_flst	*prev;
	char			*name;
	int				type;
	off_t			size;
	int				min;
	int				max;
	ino_t			st_ino;
	char			*links;
	long int		mtime;
	char			*date;
	char			*grp;
	char			*pwd;
	char			right[11];
	unsigned long	link;
	char			fltype;
	char			*path;
	struct s_flst	*next;
}						t_flst;

typedef struct			s_size
{
	int link;
	int	user;
	int group;
	int size;
	int	min;
	int max;
}						t_size;

typedef struct			s_list
{
	int			size;
	int			n;
	long long	totalb;
	char		*path;
	t_flst		*begin;
	t_flst		*end;
}						t_list;

int						main(int ac, char **av);
void					recursive(t_list *st);

char					*ft_add_char(char *str, char c, char *pos);
void					ft_joindel(char **str, char *s1, char *s2);
int						ft_nblen(off_t nb);
int						arg_nbr(void);
char					*recup_name(char *str);

void					ft_tab_rev(char ***tab, int begin);
int						ft_tabtool(char **tab, char *task);
char					**tab_del_str(char **tab, int i);

void					opt_del(void);
int						opt(char *s);
int						option(char **av);

void					ft_tab_sort2(char **tab, long int *tab2, int begin);
void					ft_tab_sort(char **tab, int begin);
void					place(t_list *list, unsigned char mode);

char					**clean_av(char **av, int i);
void					ft_sort_params(char **tab);

char					file_type(t_stat stats);
void					protection(t_flst *new, t_stat stats);
void					ft_date(t_flst *new, t_stat stats);
int						infix(t_flst *new, t_list *st);
t_size					upsize(t_list *st);
void					repo(t_list *folder, char *path, t_dir *rep);
void					acl(t_flst *new);

void					mcreate(t_flst **new);
void					mdestroy(t_flst **destroy);
void					list_c(t_list *list);
void					add_right(t_list *list, t_flst *new);
void					list_clean(t_list *list);
int						move_left(t_list *list, t_flst *mv);

void					print_params(char **tab);
void					print_repo(t_list *params);
void					aff_file_params(t_flst *prt, t_size upper, int n);
void					print_folder(char *path);

#endif
