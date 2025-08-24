/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 07:55:14 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/23 12:17:30 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*res;
	size_t			len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	len = 0;
	while (*s1)
		res[len++] = *s1++;
	while (*s2)
		res[len++] = *s2++;
	res[len] = '\0';
	return (res);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if ((unsigned char)c == '\0')
	{
		return ((char *)&str[i]);
	}
	return (NULL);
}

void	cleanup_config(t_config *cfg)
{
	if (!cfg)
		return ;
	if (cfg->texture_no)
		free(cfg->texture_no);
	if (cfg->texture_so)
		free(cfg->texture_so);
	if (cfg->texture_we)
		free(cfg->texture_we);
	if (cfg->texture_ea)
		free(cfg->texture_ea);
	if (cfg->map_lines)
		free_split(cfg->map_lines);
}
