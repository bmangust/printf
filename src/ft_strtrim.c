/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 01:28:37 by akraig            #+#    #+#             */
/*   Updated: 2019/12/21 17:46:51 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_trimmed_strlen(char const *s)
{
	int i;
	int cnt;
	int cntsp;

	i = 0;
	cnt = 0;
	cntsp = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			cntsp++;
		else
		{
			cntsp = 0;
		}
		cnt++;
		i++;
	}
	cnt -= cntsp;
	return (cnt);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		len;
	char	*copy;

	i = 0;
	j = 0;
	if (s != 0)
	{
		len = ft_trimmed_strlen(s);
		copy = (char*)malloc((len + 1) * sizeof(char));
		if (copy)
		{
			while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
				i++;
			while (j < len)
				copy[j++] = s[i++];
			copy[j] = '\0';
			return (copy);
		}
	}
	return (NULL);
}
