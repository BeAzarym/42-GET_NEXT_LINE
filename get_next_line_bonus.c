/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchabeau <cchabeau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:06:41 by cchabeau          #+#    #+#             */
/*   Updated: 2023/02/24 18:57:55 by cchabeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	check_endline(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	while (i < BUFFER_SIZE)
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (i + 1);
		i++;
	}
	return (i);
}

static char	*get_line(char *line, char *buffer, int *check_newline, int fd)
{
	int		line_size;
	int		read_check;
	char	read_buffer[BUFFER_SIZE + 1];

	while (*check_newline == -1)
	{
		ft_bzero(read_buffer, (BUFFER_SIZE + 1));
		read_check = read(fd, read_buffer, BUFFER_SIZE);
		if (read_check == -1)
		{
			free(line);
			ft_bzero(buffer, (BUFFER_SIZE + 1));
			return (NULL);
		}
		line_size = check_endline(read_buffer);
		ft_strlcpy(buffer, &read_buffer[line_size], (BUFFER_SIZE + 1));
		ft_strlcpy(read_buffer, read_buffer, line_size + 1);
		line = ft_strjoin(line, read_buffer, check_newline);
		if (read_check == 0)
		{
			ft_bzero(buffer, BUFFER_SIZE + 1);
			break ;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			check_newline;

	if ((fd < 0 || fd >= FOPEN_MAX) || BUFFER_SIZE <= 0)
		return (NULL);
	check_newline = -1;
	line = ft_strdup(buffer[fd], &check_newline);
	if (!line)
		return (NULL);
	ft_strlcpy(buffer[fd], &buffer[fd][check_newline + 1], BUFFER_SIZE + 1);
	line = get_line(line, buffer[fd], &check_newline, fd);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
