#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <stdio.h> // printf
# include <dirent.h>
# include <sys/types.h> 
# include <sys/stat.h> //stat fonction
# include <errno.h> // erreurs
# include <time.h> //ctime fonction
# include <pwd.h> //passwd
# include <grp.h> //groups
# include <string.h>
# include <sys/acl.h>
# include <sys/xattr.h>

// #include <attr/xattr.h>


# define MAJOR(x)((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x)((int32_t)((x) & 0xffffff))

typedef struct passwd	t_pwd; 
typedef struct dirent	t_dir;
typedef struct stat		t_stat;
typedef struct group	t_group;
typedef struct time_t	t_time;


typedef struct		s_flst
{
	struct			s_flst *prev;
	char			*name;//nom
	int				type;
	off_t			size;
	int				min;
	int				max;
	ino_t			st_ino;
	char			*links;
	long int		mtime;//Heure dernière modification	
	char			*date;
	char			*grp;
	char			*pwd;
	char			right[11];
	unsigned long	link;
	char			fltype;
	char			*path;
	struct			s_flst *next;
}					t_flst;

typedef struct 		s_size
{
	int link;
	int	user;
	int group;
	int size;
	int	min;
	int max;
}					t_size;

typedef struct		s_list
{
	int size;
	int n;
	long long	totalb;
	char		*path;
	t_flst		*begin;
	t_flst		*end;
}					t_list;

int		main(int ac, char **av);
void	recursive(t_list *st);

//tools
char	*ft_add_char(char *str, char c, char *pos);
void	ft_joindel(char **str, char *s1, char *s2);
int		ft_nblen(off_t nb);
int		arg_nbr(void);
char	*recup_name(char *str);

//tabtools
void	ft_tab_rev(char ***tab, int begin);
int		ft_tabtool(char **tab, char *task);
char	**tab_del_str(char **tab, int i);

//ls_options
void	opt_del(void);
int		search_opt(char *s);
int		option(char **av);

//sorts
void	ft_tab_sort2(char **tab, long int *tab2, int begin);
void	ft_tab_sort(char **tab, int begin);
void	place(t_list *list, unsigned char mode);

//args
char	**clean_av(char **av, int i);
void	ft_sort_params(char **tab);

//data
char	file_type(t_stat stats);
void	protection(t_flst *new, t_stat stats);
void	ft_date(t_flst *new, t_stat stats);
int		infix(t_flst *new, t_list *st);
t_size 	upsize(t_list *st);
void	repo(t_list *folder, char *path, t_dir *rep);
void	acl(t_flst *new);

//list
void	mcreate(t_flst **new);
void	mdestroy(t_flst **destroy);
void	list_c(t_list *list);
void	add_right(t_list *list, t_flst *new);
void	list_clean(t_list *list);
int		move_left(t_list *list, t_flst *mv);

//print
void	print_params(char **tab);
void	print_repo(t_list *params);
void	aff_file_params(t_flst *prt, t_size upper, int n);
void	print_folder(char *path);

#endif

// struct dirent { /* when _DARWIN_FEATURE_64_BIT_INODE is defined */
// 	ino_t      d_fileno;     /* file number of entry */
// 	__uint64_t d_seekoff;    /* seek offset (optional, used by servers) */
// 	__uint16_t d_reclen;     /* length of this record */
// 	__uint16_t d_namlen;     /* length of string in d_name */
// 	__uint8_t  d_type;       /* file type, see below */
// 	char    d_name[1024];    /* name must be no longer than this */
// };

// -l, -R, -a, -r et -t

// struct stat {
    // dev_t     st_dev;      /* ID du périphérique contenant le fichier */
    // ino_t     st_ino;      /* Numéro inœud */
    // mode_t    st_mode;     /* Protection */
    // nlink_t   st_nlink;    /* Nb liens matériels */
    // uid_t     st_uid;      /* UID propriétaire */
    // gid_t     st_gid;      /* GID propriétaire */
    // dev_t     st_rdev;     /* ID périphérique (si fichier spécial) */
    // off_t     st_size;     /* Taille totale en octets */
    // blksize_t st_blksize;  /* Taille de bloc pour E/S */
    // blkcnt_t  st_blocks;   /* Nombre de blocs alloués */
    // time_t    st_atime;    /* Heure dernier accès */
    // time_t    st_mtime;    /* Heure dernière modification */
    // time_t    st_ctime;    /* Heure dernier changement état */
// };

// S_ISREG(m)	//un fichier ordinaire ?
// S_ISDIR(m)	//un répertoire ?
// S_ISCHR(m)	//un périphérique en mode caractère ?
// S_ISBLK(m)	//un périphérique en mode bloc ?
// S_ISFIFO(m)	//une FIFO (tube nommé) ?
// S_ISLNK(m)	//un lien symbolique ? (Pas dans POSIX.1-1996).
// S_ISSOCK(m)	//une socket ? (Pas dans POSIX.1-1996).

// struct passwd {
//     char   *pw_name;   /* Nom d'utilisateur */
//     char   *pw_passwd; /* Mot de passe de l'utilisateur */
//     uid_t   pw_uid;    /* Identifiant de l'utilisateur */
//     gid_t   pw_gid;    /* Identifiant du groupe de l'utilisateur */
//     char   *pw_gecos;  /* Nom réel */
//     char   *pw_dir;    /* Répertoire personnel */
//     char   *pw_shell;  /* Interpréteur de commande */
// };

// struct group {
//         char    *gr_name;       /* group name */
//         char    *gr_passwd;     /* group password */
//         gid_t   gr_gid;         /* group id */
//         char    **gr_mem;       /* group members */
// };

// void insertion_sort(int *a, int n) 
// {
// 	size_t i = 1;
// 	int tmp;
// 	size_t j;

// 	while (i < n) 
// 	{
// 		int tmp = a[i];
// 		j = i;
// 		while(j > 0 && tmp < a[j - 1]) 
// 		{
// 			a[j] = a[j - 1];
// 			--j;
// 		}
// 		a[j] = tmp;
// 		i++;
// 	}
// }

// errno