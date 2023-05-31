/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:20:20 by ojimenez          #+#    #+#             */
/*   Updated: 2023/05/31 14:45:39 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(char *buffer, int fd)
{
	char	*tmp;
	size_t	numchar;
	size_t	i;

	i = 0;
	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	numchar = read(fd, tmp, BUFFER_SIZE);
	if (numchar <= 0)
		return (NULL);
	while (tmp[i] != '\n')
	{
		buffer[i] = tmp[i];
		i++;
	}
	free(tmp);
	buffer[i] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;

	if (fd < 0)
		return (NULL);
	buffer = ft_read_line(buffer, fd);
	if (!buffer)
		return (NULL);
	return (buffer);
}
