/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 22:52:00 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/12 11:43:46 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	words_counter(char const *s, char c)
{
	int		i;
	int		w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if (s[i] == c && s[i])
			i++;
		else if (s[i] != c && s[i])
		{
			w++;
			i++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (w);
}

static size_t	word_length(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static void	clean(char **split, int c)
{
	while (c >= 0)
	{
		free(split[c]);
		c--;
	}
	free(split);
}

static char	*next_word(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s && *s == c)
		s++;
	return ((char *)s);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		words;
	char		**split;

	i = 0;
	if (!s)
		return (NULL);
	words = words_counter((char *)s, c);
	split = (char **)malloc((words + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (i < words)
	{
		s = next_word(s, c);
		split[i] = ft_substr(s, 0, word_length(s, c));
		if (split[i] == NULL)
		{
			clean(split, i);
			return (NULL);
		}
		i++;
		s += word_length(s, c);
	}
	split[words] = NULL;
	return (split);
}
