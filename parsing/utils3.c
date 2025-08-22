/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 07:52:52 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/22 19:05:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	set_texture(char **target, char *value, char *err_msg)
{
	if (*target)
		error(err_msg);
	*target = value;
}

void	check_commas(char *value)
{
	int	i;

	if (!value || ft_strlen(value) == 0 || value[0] == ',')
		error("Invalid color format: starts with comma or empty");
	i = 0;
	while (value[i])
	{
		if (value[i] == ',' && (value[i + 1] == ',' || value[i + 1] == '\0'))
			error("Invalid color format: bad comma placement");
		i++;
	}
}
