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

char	*clean_av2(char *str)
{
	int		n;
	char	*s;
	t_stat	st;

	if ((n = lstat(str, &st)) == 0 && !S_ISLNK(st.st_mode))
		return (ft_strdup(str));
	else if (S_ISLNK(st.st_mode) && (n = stat(str, &st)) == 0)
	{
		if (search_opt('l') || !S_ISDIR(st.st_mode))
			return (ft_strdup(str));
		if (!search_opt('l') && S_ISDIR(st.st_mode))
		{
			s = ft_strnew(1024);
			s[readlink(str, s, 1024)] = '\0';
			return (s);
		}
	}
	if (n != 0)
		my_printf("ls: %s: No such file or directory\n", 2, str);
	return (NULL);
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
		new[x] = clean_av2(av[i]);
		new[x] == NULL ? 0 : x++;
		i++;
	}
	return (new);
}
