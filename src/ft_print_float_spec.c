/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float_spec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 20:00:18 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

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

	if (prec == 0)
		nmbr[1] = '\0';
	if ((e <= 10 && e >= 0) || (e > -9 && e < 0))
		exp = (e <= 10 && e > 0) ? ft_strjoin("e+0", ft_itoa(e - 1)) :
			  ft_strjoin("e-0", ft_itoa(-e + 1));
	else if (e > 10 || e <= -9)
		exp = (e > 10) ? ft_strjoin("e+", ft_itoa(e - 1)) :
			  ft_strjoin("e-", ft_itoa(-e + 1));
	conv_float = ft_strjoin(nmbr, exp);
	return (conv_float);
}

static char	*float_e_2(char *nmbr, int e, int prec, t_parse *p)
{
	char *conv_float;
	char *intg;
	char *fract;

	if (ft_strchr(nmbr, '.'))
	{
		intg = ft_strsub(nmbr, 0, 1);
		fract = ft_strsub(nmbr, 2, ft_strlen(nmbr) - 2);
	}
	p->E = 1;
	fract = round_fractional(fract, p->prec, 0, p);
	if (p->E && intg[0] < '9')
		intg[0] += 1;
	else if (p->E)
	{
		free(intg);
		intg = ft_strdup("1");
		e += 1;
		fract = add_symbols(fract, '0', 1, 0);
		fract[p->prec] = '\0';
	}
	fract = add_symbols(fract, '.', 1, 0);
	nmbr = ft_strjoin(intg, fract);
	conv_float = float_e_exp(nmbr, e, prec, p);
	free(nmbr);
	return (conv_float);
}

char		*float_e(char *intg, int prec, t_parse *p)
{
	int		i;
	int		e;
	char	*conv_float;

	(!ft_strchr(intg, '.')) ? intg = add_symbols(intg, '.', 1, 1) : 0;
	i = (intg[0] == '0') ? 2 : 0;
	e = 0;
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

char		*float_g(char *intg, char *fract, t_parse *p)
{
	int n;
	int e;
	int i;

	e = (p->zero_prec && p->prec == 0) ? 1 : 0;
	i = 0;
	n = ft_strlen(intg);
	if (n < p->prec && (p->prec - n) > 3 && n > 1)
	{
		fract = round_fractional(fract, p->prec - n , 0, p);
		(intg[p->prec] == '.') ? intg[p->prec] = '\0' : 0;
		return (concat_parts(intg, fract, p));
	}
	else if ((p->prec == n || (p->prec - n) < 4) && intg[0] != '0' )
		intg[n] = '\0';
	else
	{
		if (intg[0] == '0' && ft_strlen(intg) == 1)
			while (fract[i++] == '0')
				e++;
		(p->prec && p->prec > 0) ? p->prec -= 1 : 0;
		fract = round_fractional(fract, p->prec + e, 0, p);
		intg = concat_parts(intg, fract, p);
		if (e > 3 || n > p->prec)
			intg = float_e(intg, p->prec, p);
	}
	return (intg);
}
