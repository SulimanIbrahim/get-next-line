/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:31:56 by suibrahi          #+#    #+#             */
/*   Updated: 2023/09/01 21:08:21 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *str, int c)
{
	char	*strp;

	if (!str)
		return (NULL);
	strp = (char *)str;
	while (*strp)
	{
		if (*strp == (char)c)
			return (strp);
		strp++;
	}
	if (c == 0)
		return (strp);
	return (NULL);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len >= ft_strlen(s))
		len = ft_strlen(s);
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	str = ft_memcpy(str, s + start, len);
	str[len] = 0;
	return (str);
}

static char	*get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_substr(buffer, 0, i);
	return (line);
}

char	*read_send(int fd, char *buffer)
{
	int		bytes;
	char	*temp;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (temp == NULL)
		return (free(buffer), NULL);
	bytes = 1;
	if (!buffer)
		buffer = ft_strdup("");
	while (!(ft_strchr(buffer, '\n') && bytes > 0))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (!temp)
			return (free(buffer), free(temp), NULL);
		if (bytes == -1)
			return (free(buffer), free(temp), NULL);
		if (bytes == 0)
			break ;
		temp[bytes] = '\0';
		buffer = ft_strjoin(buffer, temp);
	}
	free (temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483648)
		return (NULL);
	buffer = read_send(fd, buffer);
	line = get_line(buffer);
	buffer = separate(buffer);
	if (!buffer)
		return (free(line), NULL);
	return (line);
}
