#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#	define BUFFER_SIZE 10
# endif

char    *get_next_line(int fd);
int		ft_strlen(char *s);
char	*ft_strdup(char *s);
char	*ft_strchr(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_calloc(size_t count, size_t size);

#endif
