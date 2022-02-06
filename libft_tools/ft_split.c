/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:47:07 by nick              #+#    #+#             */
/*   Updated: 2022/02/06 22:08:43 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tools.h"

static char	*get_next_word(char const **s, char c)
{
	while (**s && **s == c)
		(*s)++;
	return ((char *)*s);
}

static char	*get_next_delim(char const **s, char c)
{
	while (**s && **s != c)
		(*s)++;
	return ((char *)*s);
}

static size_t	count_words(char const *s, char c)
{
	size_t	nwords;

	nwords = 0;
	while (*s)
	{
		get_next_word(&s, c);
		if (*s)
			nwords++;
		get_next_delim(&s, c);
	}
	return (nwords);
}

static size_t	fill_words(char const *s, char c, char **words, size_t nwords)
{
	size_t	i;
	size_t	word_size;
	char	*next_word;
	char	*next_delim;

	i = 0;
	while (i < nwords)
	{
		next_word = get_next_word(&s, c);
		next_delim = get_next_delim(&s, c);
		word_size = next_delim - next_word + 1;
		words[i] = (char *)malloc(sizeof(char) * word_size);
		if (!words[i])
			return (i);
		ft_strlcpy(words[i], next_word, word_size);
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	nwords;
	size_t	n_filled_words;
	size_t	i;

	if (!s)
		return (NULL);
	nwords = count_words(s, c);
	words = (char **)malloc(sizeof(char *) * (nwords + 1));
	if (!words)
		return (NULL);
	n_filled_words = fill_words(s, c, words, nwords);
	if (n_filled_words != nwords)
	{
		i = 0;
		while (i < n_filled_words)
		{
			free(words[i]);
			i++;
		}
		free(words);
		return (NULL);
	}
	words[nwords] = NULL;
	return (words);
}
