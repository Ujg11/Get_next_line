/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:20:20 by ojimenez          #+#    #+#             */
/*   Updated: 2023/06/21 15:59:10 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (!newline)
		return (NULL);
	while (newline[i] != '\n' && newline[i])
		i++;
	if (newline[i] == '\0' || newline[1] == '\0')
		return (NULL);
	j = ft_strlen(newline);
	backline = ft_substr(newline, i + 1, j - i);
	if (!backline)
		return (free_buffer(&newline));
	if (backline[0] == '\0')
		return (free_buffer(&backline));
	newline[i + 1] = '\0';
	return (backline);
}

static char	*ft_read_line(char *backline, int fd, char *buffer)
{
	int		numchar;
	char	*s;

	numchar = 1;
	while (numchar > 0)
	{
		numchar = read(fd, buffer, BUFFER_SIZE);
		if (numchar > 0)
		{
			buffer[numchar] = '\0';
			backline = ft_strjoin(backline, buffer);
			s = ft_strchr(backline, '\n');
			if (s)
			{
				s = NULL;
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

char	*get_next_line(int fd)
{
	static char	*backline = {0};
	char		*newline;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	newline = ft_read_line(backline, fd, buffer);
	if (!newline)
	{
		backline = NULL;
		return (free_buffer(&newline));
	}
	backline = NULL;
	backline = ft_cutstr(newline);
	return (newline);
}
