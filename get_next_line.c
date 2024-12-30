#include "get_next_line.h"

static char	*ft_nextline(char *buffer)
{
	char	*line;
	size_t	i;
	int		j;
	size_t	buf_len;

	i = 0;
	if (!*buffer){
		free(buffer);
		return (NULL);
	}
	buf_len = ft_strlen(buffer);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc((buf_len - i) + 2, sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	j = 0;
	while (buffer[i] && i < buf_len)
		line[j++] = buffer[i++];
	free(buffer);
	return (line);	
}

static char	*ft_getline(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n') 				// skip until find \n
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));				// allocate char && \n
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')				// fill line
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*ft_reading(int fd, char *buffer)
{
	char	*buf;
	ssize_t	nb_read;									// return of read for allocat
	char 	*tmp;
	
	// reading file
	if (!buffer){
		buffer = ft_calloc(1, 1);
		// printf("buffer allocation '1 byte' [%p]\n", buffer);
		if (!buffer)
			return (NULL);
	}
	nb_read = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		// printf("buf allocation 'BUFFER_SIZE + 1' [%p]\n", buf);
	if (!buf)
		return (NULL);
	while (nb_read > 0)										// read all data until end of file
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == 0)
		{
			free(buf);
		// printf("buf free (nb_read == 0) [%p]", buf);
			return (buffer);
		}
		if (nb_read < 0){
			free(buf);
			return (NULL);}
		buf[nb_read] = '\0';
		tmp = buffer;
		// printf("tmp = buffer [%s] | &[%p]\n", tmp, tmp);
		buffer = ft_strjoin(buffer, buf);					//add reminder to new read
		free(tmp);
		// printf("tmp free (after join) [%p] | buffer[%p]\n", tmp, buffer);
		if (!buffer)
		{
			// free (buf);
		// printf("buf free (if buffer !!) [%p]\n", buf);
			return (NULL);
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
		// printf("buf free (after while) [%p]\n", buf);
	return (buffer);
}

char	*get_next_line(int	fd)
{
	static char	*buffer;									// for handling reminder
	char		*line;										// buffer for read

	// initial check
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)//check fd if open || buffer is positive || check the fd if ready for read
		return (NULL);
	buffer = ft_reading(fd, buffer);						//	read all file
	if (!buffer){
		free (buffer);
		return (NULL);}
	line = ft_getline(buffer);								//	return the line 
	buffer = ft_nextline(buffer);							//	handle reminder
	return (line);
}

// int main ()
// {
// 	int fd = open("text.txt", O_RDONLY);
	
// 	printf("return :%s:\n", get_next_line(fd));
// 	//  printf("return :%s:\n", get_next_line(fd));
// //	printf("return :%s:\n", get_next_line(fd));
// }