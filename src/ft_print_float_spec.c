/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float_spec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/02/06 20:10:57 by jbloodax         ###   ########.fr       */
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

static char *float_e_2(char *intg, int e, int prec, t_parse *p)
{
	char 	*conv_float;
	char 	*exp;

	if ((e <= 10 && e >= 0) || (e > -9 && e < 0))
		exp = (e <= 10 && e > 0) ? ft_strjoin("e+0", ft_itoa(e - 1 )) :
			  ft_strjoin("e-0", ft_itoa(-e + 1));
	else if (e > 10 || e <= -9)
		exp = (e > 10) ? ft_strjoin("e+", ft_itoa(e - 1)) :
			  ft_strjoin("e-", ft_itoa(-e + 1));
	if (prec == 0)
		intg[1] = '\0';
	conv_float = ft_strjoin(intg, exp);
	if (p->type == 'G')
		ft_strtoupper(conv_float, 1);
	return (conv_float);
}

char 	*float_e(char *intg, int prec, t_parse *p)
{
	int 	i;
	int 	e;
	char 	*conv_float;

	i = 0;
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
		i = 2;
		while (intg[i++] == '0')
			e--;
		intg = ft_strsub(intg, i - 2, ft_strlen(intg));
		intg[0] = intg[1];
		intg[1] = '.';
	}
	conv_float = float_e_2(intg, e, prec, p);
	free(intg);
	return(conv_float);
}

char 	*float_g(char *intg, char *fract, t_parse *p)
{
	int n;
	int e;
	int i;

	e = (p->zero_prec && p->prec == 0) ? 1 : 0;
	i = 0;
	n = ft_strlen(intg);
	if (n < p->prec && n > 1)
	{
		fract = round_fractional(fract, p->prec - n, 0, p);
		(intg[p->prec] == '.') ? intg[p->prec] = '\0' : 0;
		return (concat_parts(intg, fract, p));
	}
	else if (p->prec == n && intg[0] != '0')
		intg[n] = '\0';
	else
	{
		if (intg[0] == '0' && ft_strlen(intg) == 1)
			while (fract[i++] == '0')
				e++;
		fract = round_fractional(fract, p->prec + e, 0, p);
		intg = concat_parts(intg, fract, p);
		if (e > 3 || n > p->prec)
			intg = float_e(intg, p->prec - 1, p);
	}
	return (intg);
}
