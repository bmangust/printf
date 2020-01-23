/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 06:42:39 by akraig            #+#    #+#             */
/*   Updated: 2020/01/23 12:27:16 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_check(const char *src, const char *aim,
					size_t aimlen, size_t len)
{
	int i;
	int j;
	int start;

	i = 0;
	j = 0;
	while (src[i] != '\0' && aim[j] != '\0' && i < (int)len)
	{
		if (src[i] == aim[j])
		{
			if (j == 0)
				start = i;
			if (++j == (int)aimlen)
				return (start);
		}
		else
		{
			if (j != 0)
				i = start;
			j = 0;
		}
		i++;
	}
	return (-1);
}

char			*ft_strnstr(const char *src, const char *aim, size_t len)
{
	size_t	aimlen;
	int		start;

	aimlen = ft_strlen(aim);
	if (aimlen == 0)
		return ((char *)src);
	start = ft_check(src, aim, aimlen, len);
	if (start == -1)
		return (NULL);
	else
		return ((char *)&src[start]);
}
