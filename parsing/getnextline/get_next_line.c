/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:58:31 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/14 03:40:21 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_read(char **str, int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*tmp;
	int			br;

	if (!str || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	br = 1;
	while (br != 0 && (!*str || ft_strchr(*str, '\n') == NULL))
	{
		br = read(fd, buffer, BUFFER_SIZE);
		if (br < 0)
		{
			free(*str);
			return (NULL);
		}
		buffer[br] = '\0';
		tmp = ft_strdup(*str);
		free(*str);
		*str = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	return (*str);
}

static char	*get_line(char *line)
{
	int		i;

	if (!line || ft_strlen(line) == 0)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		i++;
	return (ft_substr(line, 0, i));
}

static char	*rest_func(char *reminder)
{
	int		i;
	int		j;
	char	*temp;

	if (!reminder)
		return (NULL);
	i = 0;
	while (reminder[i] != '\n' && reminder[i] != '\0')
		i++;
	if (reminder[i] == '\n')
		i++;
	if (reminder[i] == '\0')
	{
		free(reminder);
		return (NULL);
	}
	temp = malloc(ft_strlen(reminder) - i + 1);
	if (!temp)
		return (NULL);
	j = 0;
	while (reminder[i])
		temp[j++] = reminder[i++];
	temp[j] = '\0';
	free(reminder);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*reminder = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reminder = append_read(&reminder, fd);
	if (!reminder)
		return (NULL);
	line = get_line(reminder);
	reminder = rest_func(reminder);
	return (line);
}
