/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:53:52 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/09/24 19:53:55 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*g_new;
int		g_len;

void	ft_add_two_char(char *str, char c)
{
	int		i;

	free(g_new);
	g_new = malloc(sizeof(char) * (g_len + 1));
	i = 0;
	g_new[i] = c;
	while (str[++i - 1])
		g_new[i] = str[i - 1];
	g_new[i++] = c;
	g_new[i] = '\0';
}

char	*ft_add_char(char *str, char c, char *pos)
{
	int		i;

	i = -1;
	g_len = ft_strlen(str) + 2;
	g_new = malloc(sizeof(char) * g_len);
	if (ft_strcmp(pos, "right") == 0)
	{
		while (str[++i])
			g_new[i] = str[i];
		g_new[i++] = c;
		g_new[i] = '\0';
	}
	if (ft_strcmp(pos, "left") == 0)
	{
		g_new[++i] = c;
		while (str[++i - 1])
			g_new[i] = str[i - 1];
		g_new[i] = '\0';
	}
	if (ft_strcmp(pos, "two") == 0)
		ft_add_two_char(str, c);
	free(str);
	return (g_new);
}

int		ft_nblen(off_t nb)
{
	int n;

	n = 0;
	while (nb > 9)
	{
		nb = nb / 10;
		n++;
	}
	return (++n);
}

t_size	upsize(t_list *st)
{
	t_flst	*tp;
	t_size	up;

	up.link = 0;
	up.user = 0;
	up.group = 0;
	up.size = 0;
	up.min = 0;
	up.min = 0;
	tp = st->begin;
	while (tp)
	{
		if (tp->type == 'c' && tp->max != -1 && ft_nblen(tp->max) > up.max)
			up.max = ft_nblen(tp->max) + 1;
		if (tp->type == 'c' && tp->min != -1 && ft_nblen(tp->min) > up.min)
			up.min = ft_nblen(tp->min) + 1;
		ft_nblen(tp->size) > up.size ? up.size = ft_nblen(tp->size) + 1 : 0;
		ft_nblen(tp->link) > up.link ? up.link = ft_nblen(tp->link) + 1 : 0;
		ft_strlen(tp->pwd) > up.user ? up.user = ft_strlen(tp->pwd) : 0;
		ft_strlen(tp->grp) > up.group ? up.group = ft_strlen(tp->grp) + 1 : 0;
		tp = tp->next;
	}
	return (up);
}

char	*recup_name(char *str)
{
	char *ptr;

	ptr = str;
	while ((str = ft_strchr(str, '/')) && (*++str))
		ptr = str;
	return (ptr);
}
