/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailly- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 21:16:48 by tbailly-          #+#    #+#             */
/*   Updated: 2017/11/30 00:03:34 by tbailly-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
#include "libft/libft.h"

int		ft_has_newline(char **storage_pt, char *buf, char **line, int i)
{
	char	*tmp;

	tmp = *line;
	if (buf == NULL)
	{
		(*storage_pt)[i] = '\0';	
		*line = ft_strdup(*storage_pt);
	}
	else
	{
		buf[i] = '\0';
		*line = ft_strjoin(*line, buf);
	}
	if (line == NULL)
		return (-1);
	free(tmp);
	tmp = *storage_pt;
	if (buf == NULL)
		*storage_pt = ft_strsub(*storage_pt, i + 1, ft_strlen(&(*storage_pt)[i + 1]));
	else
		*storage_pt = ft_strsub(buf, i + 1, ft_strlen(&buf[i + 1]));
	if (*storage_pt == NULL)
		return (-1);
	free(tmp);
	return (1);
}

int		ft_no_newline(char **storage_pt, char *buf, char **line)
{
	char	*tmp;

	tmp = *line;
	if (buf == NULL)
		*line = ft_strdup(*storage_pt);
	else
		*line = ft_strjoin(*line, buf);
	if (line == NULL)
		return (-1);
	free(tmp);
	return (1);
}

int		ft_read_file(int fd, char **line, char **storage_pt)
{
	int		nbchr;
	char	buf[BUFF_SIZE + 1];
	int		i;
	int		ret;
	
	i = -1;
	if ((nbchr = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[nbchr] = '\0';
		//printf("Je lis %s nbchr %i *line %s storage %s\n", buf, nbchr, *line, *storage_pt);
		while(++i < nbchr)
			if (buf[i] == '\n')
				break;
		if (i == nbchr)
		{
			//printf("NO NWL\n");
			ft_no_newline(storage_pt, buf, line);
			ret = ft_read_file(fd, line, storage_pt);
		}
		else
		{
			//printf("NWL\n");
			ret = ft_has_newline(storage_pt, buf, line, i);
		}
		if (nbchr > 0)
			return (1);
		return (ret);
	}
	else if (nbchr == 0)
	{
		if (*storage_pt)
		{
			free(*storage_pt);
			*storage_pt = NULL;
		}
		return (0);
	}
	return (-1);
}

int		get_next_line(const int fd, char **line)
{
	static	char	*storage;
	char			*tmp;
	int				i;
	int				ret;

	tmp = NULL;
	i = -1;
	if (!storage)
		if (!(storage = (char*)malloc(sizeof(*storage))))
			return (-1);
	if (!(*line = (char*)malloc(sizeof(line))))
		return (-1);
	while (storage[++i] != '\0')
		if (storage[i] == '\n')
			break;
	//printf("Donc i=%i et stor '%s'\n", i, storage);
	//printf("len %zu et storage '%s'\n", ft_strlen(storage), storage);
	if (storage[i] == '\0')
	{
		//printf("NO NWL\n");
		ft_no_newline(&storage, NULL, line);
		ret = ft_read_file(fd, line, &storage);
	}
	else
	{
		//printf("NWL\n");
		ret = ft_has_newline(&storage, NULL, line, i);
	}
	return (ret);
}
