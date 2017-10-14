/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:53:52 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/09/24 19:53:55 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char	*g_opt;

void	error_opt(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\nusage: ls [-Ralrt1] [file ...]", 2);
	exit(1);
}

int		search_opt(char c)
{
	if (!g_opt)
		return (-1);
	return (ft_strchr(g_opt, c) ? 1 : 0);
}

int		option(char **av)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	g_opt = NULL;
	g_opt = ft_strdup("-");
	while (av[++i] && av[i][0] == '-' && av[i][1])
	{
		while (av[i][++j])
			g_opt = ft_add_char(g_opt, av[i][j], "right");
		j = 0;
	}
	j = 0;
	while (g_opt[++j])
		if (g_opt[j] != 'a' && g_opt[j] != 'l' && g_opt[j] != 'R' && \
			g_opt[j] != 'r' && g_opt[j] != 't' && g_opt[j] != '1')
			error_opt(g_opt[j]);
	return (i);
}
