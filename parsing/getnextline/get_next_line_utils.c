/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:28:44 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/14 04:18:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

/* ---------------- ft_strlen ---------------- */
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

/* ---------------- helper: copy string ---------------- */
static void	copy_str(char *dest, const char *src, int start)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[start + i] = src[i];
		i++;
	}
}

/* ---------------- ft_strjoin ---------------- */
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	int		length;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	length = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(length + 1);
	if (!res)
		return (NULL);
	copy_str(res, s1, 0);
	copy_str(res, s2, ft_strlen(s1));
	res[length] = '\0';
	return (res);
}

/* ---------------- ft_substr ---------------- */
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* ---------------- ft_strchr ---------------- */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
