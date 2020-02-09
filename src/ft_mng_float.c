/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mng_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:30:51 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:32:00 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_double	*get_bits(double d, t_double *num)
{
	int64_t	dl;
	char	*bits;
	char	*tmp;
	int		i;

	dl = *((long long*)&d);
	i = -1;
	bits = ft_strnew(64);
	while (++i < 64)
		bits[i] = ((dl >> (63 - i)) & 1) + '0';
	num->sign[0] = bits[0];
	num->exp = ft_strsub(bits, 1, 11);
	tmp = ft_strsub(bits, 12, 52);
	num->special = is_special_double(*num, tmp);
	num->mant = ft_strjoin("1", tmp);
	free(tmp);
	return (num);
}

t_double	*new_double(double d)
{
	t_double *num;

	num = (t_double*)malloc(sizeof(t_double));
	num->sign = ft_strnew(1);
	num->exp = NULL;
	num->mant = NULL;
	num = get_bits(d, num);
	return (num);
}

void		free_double(t_double *num)
{
	free(num->sign);
	free(num->exp);
	free(num->mant);
	free(num->special);
	free(num);
}

int64_t		bin_to_dec(char *bin)
{
	int i;
	int len;
	int dec;

	len = ft_strlen(bin);
	i = len--;
	dec = 0;
	while (--i >= 0)
		if (bin[i] == '1')
			dec += ft_pow(2, len - i);
	return (dec);
}

int			find_last_digit(char *mant)
{
	int i;

	i = (int)ft_strlen(mant) - 1;
	while (i >= 0 && mant[i] != '1')
		i--;
	return (i);
}
