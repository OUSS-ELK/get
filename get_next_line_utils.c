#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[++i]);
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		s_l;
	int		i;

	if	(!s)
		return (NULL);
	s_l = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * s_l + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < s_l)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*s;
	int		x;
	s = malloc(count * size);
	if (!s)
		return (NULL);
	x = 0;
	while (x < count * size){
		s[x] = '\0';
		x++;
	}
	return (s);
}


char	*ft_strchr(char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s != c)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	if (!dst || !src)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

void concat(char *str, char *s1, char *s2)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while(s1[i])
	{
		str[x] = s1[i];
		i++;
		x++;
	}
	i = 0;
	while(s2[i])
	{
		str[x] = s2[i];
		i++;
		x++;
	}
	str[x] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*stj;
	int		s1_l;
	int		s2_l;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_l = ft_strlen(s1);	
	s2_l = ft_strlen(s2);
	stj = (char *)malloc(s1_l + s2_l + 1);
	if (!stj)
		return (NULL);
	concat(stj, s1, s2);
	return (stj);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		s_l;
	int		end;
	int		i;

	if (!s)
		return (NULL);
	s_l = ft_strlen(s);
	if (len == 0 || start >= s_l)
		return (ft_strdup(""));
	s = s + start;
	s_l = ft_strlen(s);
	if (s_l > len)
		s_l = len;
	str = malloc(s_l + 1);
	printf("s_l %d + 1\n", s_l);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
