/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joteixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:59:05 by joteixei          #+#    #+#             */
/*   Updated: 2021/11/08 16:10:13 by joteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *source, size_t num)
{
	size_t	index;

	index = 0;
	if (!dest && !source)
		return (0);
	while (index < num)
	{
		((unsigned char *)dest)[index] = ((unsigned char *)source)[index];
		index++;
	}
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strdup(const char *src)
{
	char	*str;
	int		len;
	int		index;

	if (src)
	{
		index = 0;
		len = ft_strlen(src);
		if (!len)
			return (NULL);
		str = malloc((len + 1) * sizeof(char));
		if (!str)
			return (NULL);
		while (src[index])
		{
			str[index] = src[index];
			index++;
		}
		str[index] = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_strchr(const char *str, int c)
{
	int	index;

	if (str)
	{
		index = 0;
		if (str[index] == (char)c)
			return ((char *)str);
		while (str[index++])
			if (str[index] == (char)c)
				return ((char *)str + index);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*temp;
	int		total_len;
	int		i;
	int		j;

	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((total_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	temp = str;
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	ft_memcpy(temp, s1, i);
	ft_memcpy(temp + i, s2, j);
	temp[i + j] = '\0';
	return (str);
}
