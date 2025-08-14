/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:58:07 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/14 03:03:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static size_t	count_word(char const *s, char c)
{
	int		i;
	size_t	count;
	int		word;

	i = 0;
	count = 0;
	while (s[i])
	{
		word = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			if (word == 0)
				count++;
			word = 1;
			i++;
		}
	}
	return (count);
}

static char	**free_s(char **split, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
		free(split[i++]);
	free(split);
	return (NULL);
}

static char	**fill_words(char **split, char const *s, char c, size_t word_count)
{
	size_t	i;
	size_t	j;
	size_t	word_start;

	j = 0;
	i = 0;
	while (s[i] && j < word_count)
	{
		while (s[i] == c && s[i])
			i++;
		word_start = i;
		while (s[i] != c && s[i])
			i++;
		if (i > word_start)
		{
			split[j] = ft_substr(s, word_start, i - word_start);
			if (!split[j])
				return (free_s(split, j));
			j++;
		}
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char		**split;
	size_t		word_count;

	if (!s)
		return (NULL);
	word_count = count_word(s, c);
	split = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!split)
		return (NULL);
	return (fill_words(split, s, c, word_count));
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}
