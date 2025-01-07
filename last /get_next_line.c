/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouelkhar <ouelkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:10:36 by ouelkhar          #+#    #+#             */
/*   Updated: 2025/01/07 18:16:08 by ouelkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_nextline(char *buffer)
{
	char	*line;
	size_t	i;
	int		j;
	size_t	s_l;

	if (!*buffer)
		return (free(buffer), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	s_l = ft_strlen(buffer);
	line = ft_calloc((s_l - i) + 1, sizeof(char));
	if (!line)
		return (free(buffer), NULL);
	j = 0;
	while (buffer[i] && i < s_l)
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
		return (free(buffer), NULL);
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
			return (free(buffer), NULL);
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
		return (free(buffer), NULL);
	buffer = ft_read(buffer, buf, fd);
	if (!buffer)
		return (free(buf), NULL);
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
		return (NULL);
	line = ft_getline(buffer); 
	buffer = ft_nextline(buffer);
	return (line);
}
