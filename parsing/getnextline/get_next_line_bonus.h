/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 07:53:42 by zkharbac          #+#    #+#             */
/*   Updated: 2024/12/05 09:27:02 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char *get_next_line(int fd);
int ft_strlen(const char *s);
char *ft_strdup(const char *s1);
char *ft_strjoin(const char *s1, const char *s2);
char *ft_substr(const char *s, unsigned int start, size_t len);
char *ft_strchr(const char *s, int c);

#endif