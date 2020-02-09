/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:03:40 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 19:03:53 by jbloodax         ###   ########.fr       */
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
