/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 07:49:56 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/13 08:00:42 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 9223372036854775807ULL && sign == 1)
			return (-1);
		if (result > 9223372036854775807ULL && sign == -1)
			return (0);
		i++;
	}
	return (result * sign);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	char	*str;
	size_t	i;

	if (count == 0 || size == 0)
		return (malloc(1));
	if (count > (size_t)-1 / size)
		return (NULL);
	total = count * size;
	str = (char *)malloc(total);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < total)
		str[i++] = 0;
	return (str);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
