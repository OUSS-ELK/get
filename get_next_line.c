#include "get_next_line.h"

static char	*ft_joining(char *buffer, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, buf);
	free(buffer);
	return (tmp);
}

static char	*ft_nextline(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	i++;
	line = ft_calloc((ft_strlen(buffer) + 2), sizeof(char));
	i = 0;
	while (buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (line);	
}

static char	*ft_getline(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc(i + 2, sizeof(char));
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		line[j++] = buffer[i++];
	free(buffer);
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*ft_reading(int fd, char *buffer)
{
	char	*buf;
	ssize_t	nb_read;									// return of read for allocat
	
	// reading file
	nb_read = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (nb_read > 0)										// read all data until end of file
	{
		nb_read = read(fd, buf, BUFFER_SIZE);	
		if (nb_read < 0){
			free(buf);
			return (NULL);
		}
		buf[nb_read] = '\0';
		buffer = ft_joining(buffer, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (buffer);
}

char	*get_next_line(int	fd)
{
	static char	*buffer;									// for handling reminder
	char		*line;										// buffer for read

	// initial check
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)// check fd if open || buffer is positive || check the fd if ready for read
		return (NULL);
	buffer = ft_reading(fd, buffer);
	line = ft_getline(buffer);
	buffer = ft_nextline(buffer);
	return (line);
}

int main ()
{
	int fd = open("text.txt", O_RDONLY);
	char *line;

	line = get_next_line(fd); 
	while (1){
	printf("return :%s:\n", line);
	if (line == NULL)
		break ;
	}
	return (0);
}
