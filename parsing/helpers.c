/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 07:05:45 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/13 07:40:33 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	error(const char *msg)
{
	write(2, "Error\n", 6);
	while (*msg)
		write(2, msg++, 1);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

int	is_all_digits(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

char	*str_trim(char *str)
{
	int		start;
	int		end;
	int		i;
	char	*trimmed;

	start = 0;
	end = 0;
	while (str[end])
		end++;
	end--;
	while (str[start] == ' ' || str[start] == '\t')
		start++;
	while (end >= start
		&& (str[end] == ' ' || str[end] == '\t' || str[end] == '\n'))
		end--;
	trimmed = malloc(end - start + 2);
	if (!trimmed)
		error("Memory allocation failed");
	i = 0;
	while (start <= end)
		trimmed[i++] = str[start++];
	trimmed[i] = '\0';
	return (trimmed);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}
