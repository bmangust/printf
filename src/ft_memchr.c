/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:25:14 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:25:20 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	size_t			i;
	unsigned char	*p_arr;

	p_arr = (unsigned char *)arr;
	i = 0;
	if (arr)
	{
		while (i < n)
		{
			if (p_arr[i] == (unsigned char)c)
				return (&p_arr[i]);
			i++;
		}
	}
	return (NULL);
}
