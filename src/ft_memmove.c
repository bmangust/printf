/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 04:14:34 by akraig            #+#    #+#             */
/*   Updated: 2019/09/17 13:26:28 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*p_dst;
	unsigned char	*p_src;

	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	if (p_dst > p_src)
	{
		i = len;
		while (i > 0)
		{
			p_dst[i - 1] = p_src[i - 1];
			i--;
		}
	}
	else if (p_dst < p_src)
	{
		i = 0;
		while (i < len)
		{
			p_dst[i] = p_src[i];
			i++;
		}
	}
	return (dst);
}
