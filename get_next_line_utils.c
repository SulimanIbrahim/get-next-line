/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 00:43:42 by suibrahi          #+#    #+#             */
/*   Updated: 2023/09/01 20:35:42 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (d == s || (d == NULL && s == NULL ))
		return (d);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = (char *)malloc(ft_strlen(s1) + 1);
	if (s2 == NULL)
	{
		return (0);
	}
	s2 = ft_memcpy(s2, s1, ft_strlen(s1) + 1);
	return (s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*strjoin;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	strjoin = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (strjoin == NULL)
		return (free (s1), (NULL));
	while (s1[i] != '\0')
	{
		strjoin[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		strjoin[i + j] = s2[j];
		j++;
	}
	strjoin[i + j] = '\0';
	if (s1)
		free(s1);
	return (strjoin);
}

char	*separate(char *next_line)
{
	char	*temp;
	int		i;
	int		j;

	if (!next_line)
		return (NULL);
	i = 0;
	j = 0;
	while (next_line[i] && next_line[i] != '\n')
		i++;
	if (next_line[i] == '\n')
		i++;
	temp = (char *)malloc(ft_strlen(next_line) - i + 1);
	if (!temp)
		return (free(next_line), (NULL));
	if (*next_line == '\0')
		return (free(next_line), free(temp), (NULL));
	while (next_line[i] != '\0')
		temp[j++] = next_line[i++];
	temp[j] = '\0';
	free(next_line);
	return (temp);
}
