/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:58:02 by zkharbac          #+#    #+#             */
/*   Updated: 2024/12/05 09:28:07 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char *append_read(char **str, int fd)
{
    char buffer[BUFFER_SIZE + 1];
    char    *tmp;
    int br;

    if (!str || fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    br = 1;
    while (br != 0 && (!*str || ft_strchr(*str, '\n') == NULL))
    {
        br = read(fd, buffer, BUFFER_SIZE);
        if (br < 0)
        {
            free(*str);
            return NULL;
        }
        buffer[br] = '\0';
        tmp = ft_strjoin(*str, NULL);
        free(*str);
        *str = ft_strjoin(tmp, buffer);
        free(tmp);
    }
    return (*str);
}

static char *get_line(char *line)
{
    int i = 0;

    if (!line || ft_strlen(line) == 0)
        return NULL;

    while (line[i] != '\n' && line[i] != '\0')
        i++;
    if (line[i] == '\n')
        i++;
    return ft_substr(line, 0, i);
}

static char *rest_func(char *reminder)
{
    int i = 0, j = 0;
    char *temp;

    if (!reminder)
        return NULL;

    while (reminder[i] != '\n' && reminder[i] != '\0')
        i++;
    if (reminder[i] == '\n')
        i++;
    if (reminder[i] == '\0')
    {
        free(reminder);
        return NULL;
    }
    temp = malloc(ft_strlen(reminder) - i + 1);
    if (!temp)
        return NULL;
    while (reminder[i])
        temp[j++] = reminder[i++];
    temp[j] = '\0';
    free(reminder);
    return temp;
}

char *get_next_line(int fd)
{
    static char *reminder [OPEN_MAX];
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    reminder[fd] = append_read(&reminder[fd], fd);
    if (!reminder)
        return NULL;
    line = get_line(reminder[fd]);
    if(!line)
    {
		free(reminder[fd]);
		reminder[fd] = NULL;
		return (NULL);
	}
    reminder[fd]= rest_func(reminder[fd]);
    return line;
}

int main()
{
   int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);
printf("File1: %s", get_next_line(fd1));
printf("File2: %s", get_next_line(fd2));

}
