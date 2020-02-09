/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:10:52 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 19:11:06 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strappend(char const *src, char *dst, int start)
{
	int i;
	int j;

	i = 0;
	j = start;
	while (src[i])
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	return (j);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len;
	char	*s;

	i = 0;
	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	else if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		s = (char*)malloc((len + 1) * sizeof(char));
		if (s)
		{
			i = ft_strappend(s1, s, 0);
			i = ft_strappend(s2, s, i);
			s[i] = '\0';
			return (s);
		}
	}
	return (ft_strdup(""));
}
