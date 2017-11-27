/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailly- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 21:16:48 by tbailly-          #+#    #+#             */
/*   Updated: 2017/11/27 22:25:36 by tbailly-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
#include "libft/libft.h"

char	**ft_read_file(int fd, char **line, char **storage_pt)
{
	int		nbchr;
	char	buf[BUFF_SIZE + 1];
	int		i;
	
	i = 0;
	if ((nbchr = read(fd, buf, BUFF_SIZE)))
	{
		buf[nbchr] = '\0';
		printf("buf: '%s' et nbchr=%i\n", buf, nbchr);
		while(buf[i] != '\0')
		{
			if (buf[i] == '\n')
				break;
			i++;
		}
		if (buf[i] == '\0')
		{
			printf("Pas de \\n dans le buffer actuel : '%s'\n", buf);
			if (line)
			{
				*line = ft_strjoin(*line, buf);
				printf("1 '%s'\n", *line);
			}
			else
			{
				line = (char**)malloc(sizeof(*line));
				*line = ft_strdup(buf);
				printf("2 '%s'\n", *line);
			}
			line = ft_read_file (fd, line, storage_pt);
		}
		else
		{
			//printf("\\n dans le buffer actuel : '%s' a la pos %i\n", buf, i);
			*line = ft_strnjoin(*line, buf, i);
			//printf("ooo '%s'\n", *line);
			*storage_pt = ft_strdup(&(buf[i + 1]));
			//printf("storage '%s'\n", *storage_pt);
		}
		return (line);
	}
	return (NULL);
}

int		get_next_line(const int fd, char **line)
{
	printf("GETNEXTLINE %i\n", fd);
	
	static	char	*storage;
	int				i;

	i = 0;
	if (!storage)
	{
		line = ft_read_file(fd, line, &storage);
		printf("Premiere ligne '%s' et reste '%s'\n", *line, storage);
	}
	else
	{
		while (storage[i] != '\0')
		{
			if (storage[i] == '\n')
				break;
			i++;
		}
		if (storage[i] == '\0')
		{
			printf("Pas de \\n dans storage\n");
			//*line = ft_strndup(*line, storage, i);
			//line = ft_read_file(fd, line, &storage);
		}
		else
		{
			printf("\\n dans storage i=%i\n", i);
			//*line = ft_strncpy(*line, storage, i);
			//storage = ft_strcut(storage, 0, i);
		}
	}




	static	int	a;
	if (!a)
	{
		a = 10;
	}
	a++;

	line = (char**)malloc(sizeof(*line));
	line[0] = (char*)malloc(sizeof(line));
	line[0][0] = 'b';
	return (a);
}
