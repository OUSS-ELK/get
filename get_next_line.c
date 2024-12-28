#include "get_next_line.h"

static char	*ft_nextline(char *buffer)
{
	char	*line;
	int		i;
	int		j;
	int		buf_len;

	i = 0;
	buf_len = ft_strlen(buffer);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	i++;
	// if (i > buf_len)
	// {
	// 	free (buffer);
	// 	return (NULL);
	// }
	line = ft_calloc((buf_len - i) + 1, sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (buffer[i] && i < buf_len)
	{
		line[j++] = buffer[i++];
	}
	free(buffer);
	return (line);	
}

static char	*ft_getline(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer[0])
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	i++;
	if (buffer[i] && buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*ft_reading(int fd, char *buffer)
{
	char	*buf;
	ssize_t	nb_read;									// return of read for allocat
	
	// reading file
	if (!buffer)
		// return (NULL);
		buffer = ft_calloc(1, 1);
	nb_read = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (nb_read > 0)										// read all data until end of file
	{
		nb_read = read(fd, buf, BUFFER_SIZE);	
		if (nb_read == 0){
			free(buf);
			return (buffer);
		}
		buf[nb_read] = '\0';
		buffer = ft_strjoin(buffer, buf);					//add reminder to new read
		free(buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (buffer);
}

char	*get_next_line(int	fd)
{
	static char	*buffer;									// for handling reminder
	char		*line;										// buffer for read

	// initial check
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)// check fd if open || buffer is positive || check the fd if ready for read
		return (NULL);
//	printf("(get_function)buffer-before_read :%s:\n", buffer);
//	printf("(get_function)line-before_read :%s:\n", line);
	buffer = ft_reading(fd, buffer);						//read all file
//	printf("(get_function)buffer-after_read :%s:\n", buffer);
//	printf("(get_function)line-after_read :%s:\n", line);
	line = ft_getline(buffer);								//return the line 
	// printf("(get_function)buffer-after_getline :%s:\n", buffer);
//	printf("(get_function)line-after_getline :%s:\n", line);
	buffer = ft_nextline(buffer);							//handle reminder
	// printf("(get_function)buffer-after_nextline :%s:\n", buffer);
	return (line);
}

int main ()
{
	int fd = open("text.txt", O_RDONLY);
	
	printf("return :%s:\n", get_next_line(fd));
	// printf("return :%s:\n", get_next_line(fd));
//	printf("return :%s:\n", get_next_line(fd));
}