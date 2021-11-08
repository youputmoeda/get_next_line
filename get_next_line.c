/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joteixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:23:34 by joteixei          #+#    #+#             */
/*   Updated: 2021/11/05 17:57:10 by joteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_trim(char **store, char **buf, int len)
{
	char	*ret;
	char	*tmp;
	int		i;

	if (*store)
		i = ft_strlen(*store);
	else
		i = 0;
	ret = malloc((len + i + 1) * sizeof(char));
	if (!ret)
		return (0);
	ft_memcpy(ret, *store, i);
	ft_memcpy(ret + i, *buf, len);
	ret[len + i] = '\0';
	tmp = ft_strdup((*buf) + len);
	if (*store)
		free(*store);
	*store = tmp;
	return (ret);
}

static char	*gnl_get(char **store, int len)
{
	char	*ret;
	char	*tmp;
	int		i;

	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i != len)
	{
		ret[i] = (*store)[i];
		i++;
	}
	ret[i] = '\0';
	tmp = ft_strdup(*store + i);
	free(*store);
	(*store) = tmp;
	return (ret);
}

static char	*gnl_main(char **store, char **buf, int r)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	if (r <= 0)
	{
		if (r == 0 && *store)
		{
			ret = (*store);
			(*store) = NULL;
		}
		return (ret);
	}
	(*buf)[r] = '\0';
	tmp = ft_strchr(*buf, '\n');
	if (tmp)
		ret = gnl_trim(store, buf, (tmp - *buf) + 1);
	else
	{
		tmp = ft_strjoin(*store, *buf);
		if (*store)
			free(*store);
		*store = tmp;
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*local_var;
	char		*buffer;
	char		*line;
	int			r;

	if ((read(fd, 0, 0) == -1) || fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	r = 1;
	line = NULL;
	buffer = ft_strchr(local_var, '\n');
	if (!buffer)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (0);
		while (line == NULL && r > 0)
		{
			r = read(fd, buffer, BUFFER_SIZE);
			line = gnl_main(&local_var, &buffer, r);
		}
		free(buffer);
	}
	else
		line = gnl_get(&local_var, (buffer - local_var) + 1);
	return (line);
}
