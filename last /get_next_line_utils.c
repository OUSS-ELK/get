/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouelkhar <ouelkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:04:31 by ouelkhar          #+#    #+#             */
/*   Updated: 2025/01/04 09:24:11 by ouelkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		s_l;
	int		i;

	if (!s)
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

char	*ft_calloc(size_t count, size_t size)
{
	char	*s;
	size_t	x;

	s = malloc(count * size);
	if (!s)
		return (NULL);
	x = 0;
	while (x < count * size)
	{
		s[x] = '\0';
		x++;
	}
	return (s);
}

char	*ft_strchr(char *s, char c)
{
	if (s)
	{
		while (*s && *s != c)
			s++;
		if (*s == c)
			return (s);
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	s_l;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s_l = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(s_l + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
