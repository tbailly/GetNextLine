/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailly- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 21:19:23 by tbailly-          #+#    #+#             */
/*   Updated: 2017/11/28 21:12:51 by tbailly-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		GET_NEXT_LINE_H
# define	GET_NEXT_LINE_H
# define	BUFF_SIZE 2000

# include	<unistd.h>
# include	<stdlib.h>
# include	<string.h>
# include	<fcntl.h>

int			get_next_line(const int fd, char **line);

#endif
