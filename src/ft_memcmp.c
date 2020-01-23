/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 04:36:56 by akraig            #+#    #+#             */
/*   Updated: 2020/01/22 16:11:23 by akraig           ###   ########.fr       */
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
