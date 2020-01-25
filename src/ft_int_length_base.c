/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_length_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:59:57 by akraig            #+#    #+#             */
/*   Updated: 2020/01/25 17:01:15 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_int_length_base(int64_t value, int base)
{
	int cnt;

	cnt = 0;
	if (value <= 0) {
		if (base == 10)
			cnt++;
	}
	while (value) {
		value /= base;
		cnt++;
	}
	return (cnt);
}

int ft_uint_length_base(uint64_t value, int base)
{
    int cnt;

    cnt = 0;
    if (value <= 0) {
        if (base == 10)
            cnt++;
    }
    while (value) {
        value /= base;
        cnt++;
    }
    return (cnt);
}
