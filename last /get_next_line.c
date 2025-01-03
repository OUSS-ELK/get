/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouelkhar <ouelkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:10:36 by ouelkhar          #+#    #+#             */
/*   Updated: 2025/01/03 13:54:16 by ouelkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_nextline(char *buffer)
{
	char	*line;
	size_t	i;
	int		j;

	if (!*buffer)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc((ft_strlen(buffer) - i) + 1, sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	j = 0;
	while (buffer[i] && i < ft_strlen(buffer))
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

static char	*ft_getline(char *buffer)
{
	char	*line;
	size_t	i;

	if (!buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static void	*ft_read(char *buffer, char *buf, int fd)
{
	char	*tmp;
	ssize_t	nb_read;

	nb_read = 1;
	while (nb_read != 0)
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buf[nb_read] = '\0';
		tmp = buffer;
		buffer = ft_strjoin(buffer, buf);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (buffer);
}

static char	*ft_reading(int fd, char *buffer)
{
	char	*buf;

	if (!buffer)
	{
		buffer = ft_calloc(1, 1);
		if (!buffer)
			return (NULL);
	}
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
	{
		free(buffer);
		return (NULL);
	}
	buffer = ft_read(buffer, buf, fd);
	if (!buffer)
	{
		free(buf);
		return (NULL);
	}
	free(buf);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		if (buffer)
			free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_reading(fd, buffer);
	if (!buffer)
	{
		buffer = NULL;
		return (NULL);
	}
	line = ft_getline(buffer); 
	buffer = ft_nextline(buffer);
	return (line);
}
