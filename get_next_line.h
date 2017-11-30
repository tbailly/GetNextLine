/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailly- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 21:19:23 by tbailly-          #+#    #+#             */
/*   Updated: 2017/11/30 19:35:03 by tbailly-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 3

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

int			ft_read_file(int fd, char **line, char **storage_pt);
int			ft_has_newline(char **storage_pt, char *buf, char **line, int i);
int			ft_no_newline(char **storage_pt, char *buf, char **line);
int			get_next_line(const int fd, char **line);

#endif
