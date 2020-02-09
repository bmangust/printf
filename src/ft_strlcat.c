/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:10:21 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 19:25:54 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*d;
	size_t	n;
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	n = size;
	if (size <= dstlen)
		return (size + srclen);
	d = dst;
	while (*d && n-- > 1)
		d++;
	while (n-- > 1 && *src != '\0')
	{
		*d = *src;
		d++;
		src++;
	}
	*d = '\0';
	return (srclen + dstlen);
}
