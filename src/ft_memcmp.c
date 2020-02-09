/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:26:21 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:26:27 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	size_t			i;
	unsigned char	*p_arr1;
	unsigned char	*p_arr2;

	p_arr1 = (unsigned char *)arr1;
	p_arr2 = (unsigned char *)arr2;
	i = 0;
	while (i < n)
	{
		if (p_arr1[i] == p_arr2[i])
			i++;
		else
			return (p_arr1[i] - p_arr2[i]);
	}
	return (0);
}
