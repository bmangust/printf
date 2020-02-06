/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float_concat.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/01/25 18:06:01 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*round_fractional(char *fract, int prec, int is_int, t_parse *p)
{
	int 	i;

	if (prec > (int)ft_strlen(fract))
	{
		p->E = 0;
		return (add_symbols(fract, '0', prec - ft_strlen(fract), 1));
	}
	i = prec;
	if ((fract[i] >= '5' || is_int) && prec > 0)
	{
		p->E = (fract[i - 1] - '0' + p->E) / 10;
		if (!p->E)
			fract[prec - 1] = (fract[prec - 1] - '0' + 1) % 10 + '0';
		while (p->E == 1 && --i >= 0)
		{
			p->E = (fract[i] - '0' + 1) / 10;
			fract[i] = (fract[i] - '0' + 1) % 10 + '0';
		}
	}
	else
		p->E = 0;
	if (is_int && p->E)
		fract = add_symbols(fract, '1', 1, 0);
	if (!is_int)
		fract[prec] = '\0';
	return (fract);
}

/*
**	is_integer may be 1 for integer or -1 for fractional
*/

char	*count_exp(t_double *num, int is_integer)
{
	int		exp;
	int		diff;
	char	*bin;

	exp = bin_to_dec(num->exp);
	diff = (num->is_double) ? 1023 : 127;
	exp -= diff;
	if (exp >= 0 && exp < 53)
		return ((is_integer) ? ft_strsub(num->mant, 0, exp + 1)
								  : ft_strsub(num->mant, exp + 1, 53));
	if (exp > 52 && is_integer)
	{
		bin = add_symbols(num->mant, '0', exp - 52, 1);
		num->mant = ft_strdup("0");
	}
	else if (is_integer)
		bin = ft_strdup("0");
	else if (exp < 0)
	{
		bin = add_symbols(num->mant, '0', -exp - 1, 0);
		num->mant = NULL;
	}
	else
		bin = ft_strdup(num->mant);
	return (bin);
}

char	*get_fractional(t_double *num, t_parse *p)
{
	char	*fract;
	char	*five_power;
	char	*fract_bin;
	int 	i;
	int 	fract_len;

	i = -1;
	fract_bin = count_exp(num, 0);
	fract_len = find_last_digit(fract_bin) + 1;
	fract = ft_charstr(fract_len, '0');
	five_power = NULL;
	while (i++ < fract_len)
	{
		five_power = get_five_power(five_power, i + 1);
		if (fract_bin[i] == '1')
			sum(fract, five_power);
	}
	if (p->type == 'F' || p->type == 'f')
		fract = round_fractional(fract, p->prec, 0, p);
	else
		p->E = 0;
	free (fract_bin);
	free (five_power);
	return (fract);
}

char	*get_integer(t_double *num, t_parse *p)
{
	char	*intg;
	char	*two_power;
	char	*integer_bin;
	int 	i;
	int 	integer_len;

	i = -1;
	integer_bin = ft_strrev(count_exp(num, 1));
	p->E = find_last_digit(integer_bin);
	integer_len = p->E ? p->E / 3 + 1 : 1;
	intg = ft_charstr(integer_len, '0');
	two_power = NULL;
	while (++i <= p->E)
	{
		two_power = get_two_power(two_power, i);
		if (integer_bin[i] == '1')
			sum2(intg, two_power);
	}
	while (integer_len > 1 && intg[ft_strlen(intg) - 1] == '0')
		intg[ft_strlen(intg) - 1] = '\0';
	free (integer_bin);
	free (two_power);
	p->E = 1;
	return (intg);
}

char	*concat_parts(char *integer, char *fract, t_parse *p)
{
	char *tmp;

	if (p->E)
		integer = round_fractional(integer, ft_strlen(integer), 1, p);
	tmp = integer;
	if (ft_strlen(fract) == 0)
		return (integer);
	if (!p->zero_prec || ft_strchr("eEgG", p->type))
	{
		integer = ft_strjoin(integer, ".");
		free(tmp);
		tmp = integer;
		integer = ft_strjoin(integer, fract);
		free(tmp);
	}
	return (integer);
}
