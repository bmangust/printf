/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float_spec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/02/10 22:05:02 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*is_special_double(t_double num, char *mant)
{
	char *s;

	s = NULL;
	if (!ft_strcmp(num.exp, "11111111111") && !ft_strchr(mant, '1'))
		s = num.sign[0] == '0' ? ft_strdup("inf") : ft_strdup("-inf");
	else if (!ft_strcmp(num.exp, "11111111111"))
		s = ft_strdup("nan");
	return (s);
}

static char	*float_e_exp(char *nmbr, int e, int prec, t_parse *p)
{
	char *conv_float;
	char *exp;

	if (ft_strchr("gG", p->type))
		ft_cut_zero_fract(nmbr);
	if (prec == 0)
		nmbr[1] = '\0';
	if ((e <= 10 && e >= 0) || (e > -9 && e < 0))
		exp = (e <= 10 && e > 0) ? ft_strjoin("e+0", ft_itoa(e - 1)) :
			ft_strjoin("e-0", ft_itoa(-e + 1));
	else if (e > 10 || e <= -9)
		exp = (e > 10) ? ft_strjoin("e+", ft_itoa(e - 1)) :
			ft_strjoin("e-", ft_itoa(-e + 1));
	conv_float = ft_strjoin(nmbr, exp);
	free(nmbr);
	return (conv_float);
}

static char	*float_e_2(char *nmbr, int e, int prec, t_parse *p)
{
	char *conv_float;
	char *intg;
	char *fract;

	intg = ft_strchr(nmbr, '.') ? ft_strsub(nmbr, 0, 1) : ft_strdup(nmbr);
	fract = ft_strchr(nmbr, '.') ?
			ft_strsub(nmbr, 2, ft_strlen(nmbr) - 2) : NULL;
	if (ft_strchr("gG", p->type))
		p->prec -= p->zero_prec ? 0 : 1;
	fract = round_fractional(fract, p->prec, 0, p);
	if (p->carry && intg[0] < '9' && (p->carry = 0) == 0)
		intg[0] += 1;
	else if (p->carry)
	{
		free(intg);
		intg = ft_strdup("1");
		e += 1;
		fract = add_symbols(fract, '0', 1, 0);
		fract[p->prec] = '\0';
		p->carry = 0;
	}
	intg = concat_parts(intg, fract, p);
	conv_float = float_e_exp(intg, e, prec, p);
	return (conv_float);
}

char		*float_e(char *intg, int prec, t_parse *p, int e)
{
	int		i;
	char	*conv_float;

	!ft_strchr(intg, '.') ? intg = add_symbols(intg, '.', 1, 1) : 0;
	i = (intg[0] == '0') ? 2 : 0;
	if (intg[0] > '0')
	{
		while (intg[i++] != '.')
			e++;
		while (i-- > 1)
			intg[i] = intg[i - 1];
		intg[i + 1] = '.';
	}
	else if (intg[0] == '0')
	{
		while (intg[i++] == '0')
			e--;
		intg = ft_strsub(intg, i - 2, ft_strlen(intg));
		intg[0] = intg[1];
		intg[1] = '.';
	}
	conv_float = float_e_2(intg, e, prec, p);
	free(intg);
	return (conv_float);
}

char		*float_g(char *intg, char *fract, t_parse *p, int len)
{
	int i;
	int zero_fract;

	len = (intg[0] == '0' && ft_strlen(intg) == 1) ? 0 : len;
	i = 0;
	while (fract && fract[i] == '0' && !len)
		i++;
	if ((p->zero_prec == 0 && p->prec >= len) || i > 6)
	{
		fract = fract ? round_fractional(fract, p->prec - len + i, 0, p) : NULL;
		zero_fract = ft_is_same_chr(fract, '0');
		intg = concat_parts(intg, fract, p);
		if (p->prec != len && ft_strchr(intg, '.'))
		{
			ft_cut_zero_fract(intg);
			if (zero_fract > 0 && ft_strchr(intg, '.'))
				intg[ft_strchrn(intg, '.')] = '\0';
		}
		else if (p->prec != (int)ft_strlen(intg))
			intg = float_e(intg, ft_strlen(intg), p, 0);
		return (intg);
	}
	intg = concat_parts(intg, fract, p);
	intg = float_e(intg, p->prec - 1, p, 0);
	return (intg);
}
