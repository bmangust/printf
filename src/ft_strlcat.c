/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 05:45:54 by akraig            #+#    #+#             */
/*   Updated: 2020/01/22 16:11:23 by akraig           ###   ########.fr       */
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
