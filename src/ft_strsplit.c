/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:58:06 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 18:58:57 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wlen(char const *s, char c)
{
	int word_length;

	word_length = 0;
	while (s[word_length] != c && s[word_length] != '\0')
	{
		word_length++;
	}
	return (word_length);
}

static char	**ft_freemem(char **words, int w_num)
{
	while (w_num > -1)
	{
		ft_strdel(&(words[w_num]));
		w_num--;
	}
	free(words);
	return (NULL);
}

static char	**ft_get_words(char const *s, char c, char **words)
{
	int	w_num;
	int	k;

	w_num = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			k = 0;
			if (!(words[w_num] =
						(char *)malloc(sizeof(char) * (ft_wlen(s, c) + 1))))
				return (ft_freemem(words, w_num));
			while (*s != c && *s != '\0')
				words[w_num][k++] = *s++;
			words[w_num][k] = '\0';
			w_num++;
		}
	}
	words[w_num] = NULL;
	return (words);
}

char		**ft_strsplit(char const *s, char c)
{
	char **words;

	if (!s || !(words = (char**)malloc(sizeof(char*) * (ft_wrdcnt(s, c) + 1))))
		return (NULL);
	words = ft_get_words(s, c, words);
	return (words);
}
