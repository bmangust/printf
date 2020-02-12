/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/02/10 22:06:04 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_float_internal(t_parse *p, t_double *num)
{
	char	*integer;
	char	*fract;
	int		len_int;

	if (!p->zero_prec && !p->prec)
		p->prec = 6;
	integer = ft_strrev(get_integer(num, p));
	fract = get_fractional(num, p);
	len_int = ft_strlen(integer);
	if (ft_strchr("fFeE", p->type))
		integer = concat_parts(integer, fract, p);
	if (p->type == 'e' || p->type == 'E')
		integer = float_e(integer, p->prec, p, 0);
	else if (p->type == 'g' || p->type == 'G')
		integer = float_g(integer, fract, p, len_int);
	if (ft_strchr("FEG", p->type))
		integer = ft_strtoupper(integer, 1);
	return (integer);
}

char	*print_float(double d, t_parse *p)
{
	t_double	*num;
	char		*integer;

	num = new_double(d);
	if (num->special && ft_strchr("FEG", p->type))
		integer = ft_strtoupper(num->special, 1);
	else if (num->special)
		integer = ft_strdup(num->special);
	else
		integer = print_float_internal(p, num);
	if (ft_strchr(p->flags, '0') && !ft_strchr(p->flags, '-'))
	{
		integer = (num->sign[0] == '1' || ft_strchr(p->flags, '+')
			|| ft_strchr(p->flags, ' '))
			? add_symbols(integer, '0', p->width - ft_strlen(integer) - 1, 0)
			: add_symbols(integer, '0', p->width - ft_strlen(integer), 0);
	}
	num->sign[0] == '1' ? integer = add_symbols(integer, '-', 1, 0) : 0;
	(num->sign[0] == '0' && ft_strchr(p->flags, '+')) ?
			integer = add_symbols(integer, '+', 1, 0) : 0;
	(num->sign[0] == '0' && ft_strchr(p->flags, ' ') && p->width) ?
			integer = add_symbols(integer, ' ', 1, 0) : 0;
	free_double(num);
	return (integer);
}

void	ft_cut_zero_fract(char *fract)
{
	int	len;

	if (!fract)
		return ;
	len = ft_strlen(fract);
	while (fract[--len] == '0')
		;
	fract[len + 1] = '\0';
	if (fract[len] == '.')
		fract[len] = '\0';
}

int		ft_is_same_chr(char *str, int c)
{
	size_t i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] == c)
		i++;
	if (i == ft_strlen(str) && i != 0)
		return (1);
	return (0);
}
