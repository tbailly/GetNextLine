/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailly- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 21:16:48 by tbailly-          #+#    #+#             */
/*   Updated: 2017/12/05 16:58:35 by tbailly-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
#include "libft/libft.h"

int		ft_cannot_read(int nbchr, char **storage_pt, char **line)
{
	int	ret;

	ret = 0;
	if (nbchr == 0)
	{
		if (*storage_pt)
			ft_memdel((void**)storage_pt);
		if (*line[0] != '\0')
			ret = 1;
	}
	else
		ret = -1;
	return (ret);
}

int		ft_has_newline(char **st_pt, char *buf, char **line, int i)
{
	char	*tmp;

	tmp = *line;
	if (buf == NULL)
	{
		(*st_pt)[i] = '\0';
		*line = ft_strdup(*st_pt);
	}
	else
	{
		buf[i] = '\0';
		*line = ft_strjoin(*line, buf);
	}
	if (line == NULL)
		return (-1);
	free(tmp);
	tmp = *st_pt;
	if (buf == NULL)
		*st_pt = ft_strsub(*st_pt, i + 1, ft_strlen(&(*st_pt)[i + 1]));
	else
		*st_pt = ft_strsub(buf, i + 1, ft_strlen(&buf[i + 1]));
	if (*st_pt == NULL)
		return (-1);
	free(tmp);
	return (1);
}

int		ft_no_newline(char **storage_pt, char *buf, char **line, int fd)
{
	char	*tmp;
	int		ret;

	tmp = *line;
	if (buf == NULL)
		*line = ft_strdup(*storage_pt);
	else
		*line = ft_strjoin(*line, buf);
	if (line == NULL)
		return (-1);
	free(tmp);
	ret = ft_read_file(fd, line, storage_pt);
	return (ret);
}

int		ft_read_file(int fd, char **line, char **storage_pt)
{
	int		nbchr;
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*tmp;

	ret = 0;
	if ((nbchr = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[nbchr] = '\0';
		while ((int)ft_strlen(buf) != nbchr)
		{
			tmp = ft_memchr(buf, '\0', nbchr);
			ft_memmove(tmp, tmp + 1, ((&buf[nbchr]) - tmp));
			nbchr--;
		}
		if ((ft_memchr(buf, '\n', nbchr) - (void*)buf) >= 0)
			ret = ft_has_newline(storage_pt, buf, line,
					ft_memchr(buf, '\n', nbchr) - (void*)buf);
		else
			ret = ft_no_newline(storage_pt, buf, line, fd);
	}
	else
		ret = ft_cannot_read(nbchr, storage_pt, line);
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	static	char	*storage;
	int				i;
	int				ret;

	i = -1;
	if (line == NULL)
		return (-1);
	if (!storage && !(storage = (char*)ft_memalloc(sizeof(*storage))))
		return (-1);
	if (!(*line = (char*)malloc(sizeof(line))))
		return (-1);
	while (storage[++i] != '\0')
		if (storage[i] == '\n')
			break ;
	if (storage[i] == '\0')
	{
		if ((ret = ft_no_newline(&storage, NULL, line, fd)) == -1)
			return (-1);
	}
	else
		ret = ft_has_newline(&storage, NULL, line, i);
	return (ret);
}
