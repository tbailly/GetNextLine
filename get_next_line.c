/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailly- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 21:16:48 by tbailly-          #+#    #+#             */
/*   Updated: 2017/11/28 21:12:53 by tbailly-         ###   ########.fr       */
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
		//'printf("buf: '%s' et nbchr=%i\n", buf, nbchr);
		while(buf[i] != '\0')
		{
			if (buf[i] == '\n')
				break;
			i++;
		}
		if (buf[i] == '\0')
		{
			//printf("Pas de \\n dans le buffer actuel : '%s'\n", buf);
			if (line)
			{
				//printf("1 '%s'\n", *line);
				*line = ft_strjoin(*line, buf);
			}
			else
			{
				//printf("2 '%s'\n", *line);
				//line = (char**)malloc(sizeof(*line));
				*line = ft_strdup(buf);
			}
			line = ft_read_file(fd, line, storage_pt);
		}
		else
		{
			//printf("\\n dans le buffer actuel : '%s' a la pos %i\n", buf, i);
			if (line)
			{
				*line = ft_strnjoin(*line, buf, i);
				*storage_pt = ft_strdup(&(buf[i + 1]));
				//printf("3 '%s'\n", *line);
			}
			else
			{
				//line = (char**)malloc(sizeof(*line));
				*line = ft_strndup(buf, i);
				*storage_pt = ft_strdup(&(buf[i + 1]));
				//printf("4 '%s'\n", *line);
			}
		}
		return (line);
	}
	return (NULL);
}

char	*ft_strpop_front(char *src, int n)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(src);
	//printf("len %i et n\n", len);
	i = 0;
	if (!(ret = (char*)malloc(sizeof(*ret) * (len - n))))
		return (NULL);
	//printf("n %i et src[n] %c et len %i\n", n, src[n], len);
	while (n < len)
	{
		ret[i] = src[n];
		n++;
		i++;
	}
	//free(src);
	//src = NULL;
	ret[i] = '\0';
	//printf("stor %s and i%i\n", ret, i);
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	//printf("--------------- GETNEXTLINE\n");
	
	static	char	*storage;
	int				i;

	i = 0;
	if (!storage)
		if (!(storage = (char*)malloc(sizeof(*storage))))
			return (-1);
	if (!(line = (char**)malloc(sizeof(*line))))
		return (-1);
	if (!(*line = (char*)malloc(sizeof(line))))
		return (-1);
	
	while (storage[i] != '\0')
	{
		if (storage[i] == '\n')
			break;
		i++;
	}
	if (storage[i] == '\0')
	{
		//printf("Pas de \\n dans storage\n");
		if (storage[0] != '\0')
			*line = ft_strdup(storage);
		line = ft_read_file(fd, line, &storage);
	}
	else if (i == 0)
	{
		storage = ft_strpop_front(storage, i + 1);
		//printf("storagetirhgrt %s\n", storage);
		//return (1);
	}
	else
	{
		//printf("\\n dans storage i=%i\n", i);
		*line = ft_strndup(storage, i);
		//printf("storage avant %s et i%i\n", storage, i);
		storage = ft_strpop_front(storage, i + 1);
		//printf("storage apres %s\n", storage);
	}
	//printf("--------------- LINE %s\n--------------- STORAGE %s\n", *line, storage);
	printf("LINE %s\n", *line);

	return (-1);
}
