/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:06:21 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/08/14 20:06:23 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	line_creator(char **line, const int fd, char **str, char *buff)
{
	char	*tmp;
	int		len;
	int		ret;

	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		if (ret == -1)
			return (ret);
		buff[ret] = '\0';
		tmp = *line;
		*line = ft_strjoin(tmp, buff);
		free(tmp);
		if ((tmp = ft_strchr(*line, '\n')))
		{
			*str = ft_strdup(tmp + 1);
			len = tmp - *line;
			tmp = *line;
			*line = ft_strsub(tmp, 0, len);
			free(tmp);
			break ;
		}
	}
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char	*str = NULL;
	int			ret;
	char		buff[BUFF_SIZE + 1];
	char		*tmp;

	if (line == NULL || fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	*line = ft_strnew(BUFF_SIZE);
	if (str)
	{
		if ((tmp = ft_strchr(str, '\n')))
		{
			*line = ft_strsub(str, 0, tmp - str);
			str = tmp + 1;
			return (1);
		}
		*line = ft_strdup(str);
		str = NULL;
	}
	if ((ret = line_creator(&line[0], fd, &str, buff)) == -1)
		return (-1);
	if (!ret && !ft_strlen(*line))
		return (0);
	return (1);
}
