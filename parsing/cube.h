/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:04:43 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/13 09:31:38 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "cube.h" 
#include "getnextline/get_next_line.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 5
#endif

typedef struct s_config
{
	char *texture_no;
	char *texture_so;
	char *texture_we;
	char *texture_ea;
	int floor_color;
	int ceiling_color;
	char **map_lines;
	int map_height;
	float player_x;
	float player_y;
	char player_dir;
} t_config;

int     ft_atoi(const char *str);
void    ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void    ft_putchar_fd(char c, int fd);
void    ft_putendl_fd(char *s, int fd);
void    ft_putstr_fd(char *s, int fd);
char    **ft_split(char const *s, char c);
char    *ft_strchr(const char *s, int c);
char    *ft_strdup(const char *s1);
char    *ft_strjoin(char const *s1, char const *s2);
size_t  ft_strlen(const char *s);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char    *ft_substr(const char *s, unsigned int start, size_t len);
void	check_closed_map(char **map, int h, int w);
void	validate_map_characters(t_config *cfg);
char	**pad_map(char **lines, int height, int *width_out);
void	save_map_line(t_config *cfg, char *line);
void	free_split(char **arr);
char	*str_trim(char *str);
int	is_all_digits(char *str);
void	error(const char *msg);
char	*skip_spaces(char *str);
char	*pad_line(char *line, int width);
int	get_max_width(char **lines, int height);
void	check_cell(char **map, int y, int x, int h, int w);
int	is_player_char(char c);
int	is_valid_map_char(char c);
#endif

