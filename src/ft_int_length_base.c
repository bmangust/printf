/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_length_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:02:36 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:03:23 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_int_length_base(int64_t value, int base)
{
	int cnt;

	cnt = value == 0 ? 1 : 0;
	if (value < 0)
	{
		if (base == 10)
			cnt++;
	}
	while (value)
	{
		value /= base;
		cnt++;
	}
	return (cnt);
}

int	ft_uint_length_base(uint64_t value, int base)
{
	int cnt;

	cnt = value == 0 ? 1 : 0;
	while (value)
	{
		value /= base;
		cnt++;
	}
	return (cnt);
}
