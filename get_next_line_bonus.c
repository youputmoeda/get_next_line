/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joteixei <joteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:36:08 by joteixei          #+#    #+#             */
/*   Updated: 2022/02/09 16:40:44 by joteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*gnl_trim(char **storage, char **buffer, int len)
{
	char	*result;
	char	*tmp;
	int		i;

	if (*storage)
		i = ft_strlen(*storage);
	else
		i = 0;
	result = malloc(sizeof(char) * (len + i + 1));
	if (!result)
		return (0);
	ft_memcpy(result, *storage, i);
	ft_memcpy(result + i, *buffer, len);
	result[len + i] = '\0';
	tmp = ft_strdup((*buffer) + len);
	if (*storage)
		free(*storage);
	*storage = tmp;
	return (result);
}

static char	*gnl_get(char **storage, int len)
{
	char	*result;
	char	*tmp;
	int		i;

	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i != len)
	{
		result[i] = (*storage)[i];
		i++;
	}
	result[i] = '\0';
	tmp = ft_strdup(*storage + i);
	free(*storage);
	(*storage) = tmp;
	return (result);
}

static char	*gnl_main(char **storage, char **buff, int i)
{
	char	*result;
	char	*tmp;

	result = NULL;
	if (i <= 0)
	{
		if (i == 0 && *storage)
		{
			result = (*storage);
			(*storage) = NULL;
		}
		return (result);
	}
	(*buff)[i] = '\0';
	tmp = ft_strchr(*buff, '\n');
	if (tmp)
		result = gnl_trim(storage, buff, (tmp - *buff) + 1);
	else
	{
		tmp = ft_strjoin(*storage, *buff);
		if (*storage)
			free(*storage);
		*storage = tmp;
	}
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*buffer;
	char		*line_text;
	int			i;

	if ((read(fd, 0, 0) == -1) || fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 1;
	line_text = NULL;
	buffer = ft_strchr(storage[fd], '\n');
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (0);
		while (line_text == NULL && i > 0)
		{
			i = read(fd, buffer, BUFFER_SIZE);
			line_text = gnl_main(&storage[fd], &buffer, i);
		}
		free(buffer);
	}
	else
		line_text = gnl_get(&storage[fd], (buffer - storage[fd]) + 1);
	return (line_text);
}
