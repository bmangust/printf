/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/02/06 20:03:11 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_float_internal(t_parse *p, t_double *num)
{
	char		*integer;
	char		*fract;

	if (!p->zero_prec && !p->prec)
		p->prec = 6;
	integer = ft_strrev(get_integer(num, p));
	fract = (p->zero_prec && !ft_strchr("gG", p->type)) ?
			NULL : get_fractional(num, p);
	if (ft_strchr("fFeE", p->type))
		integer = concat_parts(integer, fract, p);
	if (p->type == 'e' || p->type == 'E')
		integer = float_e(integer, p->prec, p);
	else if (p->type == 'g' || p->type == 'G')
		integer = float_g(integer, fract, p);
	return (integer);
}

char	*print_float(double d, t_parse *p)
{
	t_double	*num;
	char		*integer;

	num = new_double(d);
	if (num->special && (p->type == 'F' || p->type == 'G' || p->type == 'E'))
		integer = ft_strtoupper(num->special, 1);
	else if (num->special)
		integer = ft_strdup(num->special);
	else
		integer = print_float_internal(p, num);
	num->sign[0] == '1' ? integer = add_symbols(integer, '-', 1, 0) : 0;
	(num->sign[0] == '0' && ft_strchr(p->flags, '+')) ?
			integer = add_symbols(integer, '+', 1, 0) : 0;
	(num->sign[0] == '0' && ft_strchr(p->flags, ' ')) ?
			integer = add_symbols(integer, ' ', 1, 0) : 0;
	free_double(num);
	return (integer);
}
