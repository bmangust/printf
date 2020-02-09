/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:30:30 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:30:35 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t n)
{
	size_t			i;
	unsigned char	*p_dst;

	i = 0;
	p_dst = (unsigned char *)dst;
	while (i < n)
	{
		p_dst[i] = c;
		i++;
	}
	return (dst);
}
