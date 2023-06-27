/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:34:57 by ojimenez          #+#    #+#             */
/*   Updated: 2023/06/27 11:07:15 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_buffer(char **buff)
{
	free(*buff);
	*buff = NULL;
	return (NULL);
}

static char	*ft_cutstr(char *newline)
{
	char	*backline;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (newline[0] == '\0')
		return (NULL);
	while (newline[i] != '\n' && newline[i])
		i++;
	j = ft_strlen(newline);
	if (newline[i] == '\n')
		backline = ft_substr(newline, i + 1, j - i);
	else
		return (NULL);
	if (!backline)
		return (NULL);
	if (backline[0] == '\0')
		return (free_buffer(&backline));
	newline[i + 1] = '\0';
	return (backline);
}

static char	*ft_read_line(int fd, char *backline)
{
	int		numchar;
	char	*buffer;

	numchar = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_buffer(&backline));
	while (numchar > 0 && !ft_strchr(backline, '\n'))
	{
		numchar = read(fd, buffer, BUFFER_SIZE);
		if (numchar > 0)
		{
			buffer[numchar] = '\0';
			backline = ft_strjoin(backline, buffer);
			if (ft_strchr(backline, '\n'))
			{
				free_buffer(&buffer);
				return (backline);
			}
		}
	}
	free_buffer(&buffer);
	if (numchar == -1)
		return (free_buffer(&backline));
	return (backline);
}

char	*clean_newline(char *line, char *newline)
{
	size_t	i;

	i = 0;
	if (!newline)
		return (free_buffer(&newline));
	while (newline[i])
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (free_buffer(&newline));
	i = 0;
	while (newline[i])
	{
		line[i] = newline[i];
			i++;
	}
	line[i] = '\0';
	free_buffer(&newline);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*backline[OPEN_MAX];
	char		*newline;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	newline = ft_read_line(fd, backline[fd]);
	if (!newline)
	{
		backline[fd] = NULL;
		return (NULL);
	}
	backline[fd] = NULL;
	free_buffer(&backline[fd]);
	backline[fd] = ft_cutstr(newline);
	line = clean_newline(line, newline);
	if (!line)
		return (free_buffer(&backline[fd]));
	return (line);
}
