/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:20:20 by ojimenez          #+#    #+#             */
/*   Updated: 2023/06/02 17:35:09 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_search_where(char *newline)
{
	size_t	i;
	size_t	w;

	i = 0;
	while (newline[i])
	{
		if (newline[i] == '\n')
		{
			w = i;
			return (w);
		}
		i++;
	}
	return (i);
}

char	*ft_cutstr(char *newline, char **backline)
{
	size_t	i;
	size_t	w;

	w = ft_search_where(newline);
	i = 0;
	newline[w++] = '\0';
	while (newline[w])
	{
		*backline[i] = newline[w];
		i++;
		w++;
	}
	return (newline);
}

char	*ft_read_line(char *backline, int fd, char *buffer)
{
	int		numchar;
	char	*aux;

	numchar = 1;
	while (1)
	{
		numchar = read(fd, buffer, BUFFER_SIZE);
		if (numchar == -1)
			return (NULL);
		if (numchar == 0)
			break ;
		buffer[numchar] = '\0';
		aux = backline;
		backline = ft_strjoin(aux, buffer);
		free (aux);
		aux = ft_strchr(backline, '\n');
		if (aux != NULL)
		{
			aux = NULL;
			return (backline);
		}
		aux = NULL;
	}
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
	if (!backline)
		backline = ft_strdup("");
	newline = ft_read_line(backline, fd, buffer);
	free(buffer);
	if (!newline)
		return (NULL);
	newline = ft_cutstr(newline, &backline);
	return (newline);
}
