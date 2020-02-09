/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 20:00:00 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	printing int
*/

int		int_length_and_update(int64_t n, t_parse *p)
{
	p->length = p->is_signed ?
			ft_int_length_base(n, 10) : ft_uint_length_base(n, 10);
	if (n < 0)
		p->length--;
	return (p->length);
}

int		is_positive(int64_t n, t_parse *p)
{
	if (p->is_signed)
		return (n >= 0) ? 1 : 0;
	return (1);
}

void	add_sign(int64_t n, t_parse *p, char **num)
{
	char *tmp;

	tmp = *num;
	if (p->is_signed && (!is_positive(n, p) || ft_strchr(p->flags, '+')))
	{
		if (!is_positive(n, p))
			*num = ft_strjoin("-", *num);
		else if (ft_strchr(p->flags, '+'))
			*num = ft_strjoin("+", *num);
		free(tmp);
	}
	else if (p->is_signed && ft_strchr(p->flags, ' ') && p->spaces == 0)
	{
		*num = ft_strjoin(" ", *num);
		free(tmp);
	}
}

char	*fill_width(t_parse *p, char *num, char sign)
{
	char	symbol;
	int		is_after;
	int		num_of_spaces;

	if (p->width > p->length)
	{
		num_of_spaces = (sign && !ft_strchr(p->flags, '-'))
			? p->width - p->length + 1 : p->width - p->length;
		symbol = (p->skip_0_flag == 0 && !ft_strchr(p->flags, '-')
				&& ft_strchr(p->flags, '0')) ? '0' : ' ';
		is_after = ft_strchr(p->flags, '-') ? 1 : 0;
		num = add_symbols(num, symbol, num_of_spaces, is_after);
		if (sign && symbol == ' ' && !ft_strchr(p->flags, '-'))
			num[p->width - p->length] = sign;
		else if (sign && !ft_strchr(p->flags, '-'))
			num[0] = sign;
	}
	return (num);
}

char	*get_int(t_parse *p, int64_t n)
{
	char *num;

	if ((p->width || p->flags) && n == 0 && p->zero_prec == 1)
	{
		num = ft_strnew(1);
		num[0] = ft_strchr(p->flags, '+') ? '+' : ' ';
		return (num);
	}
	else if (n == 0 && p->zero_prec == 1)
		return (ft_strnew(1));
	num = p->is_signed ? ft_itoa(ft_absint(n)) : ft_itoa_base(n, 10);
	if (p->prec > p->length)
		num = add_symbols(num, '0', ft_absint(p->prec - p->length), 0);
	if (n != -9223372036854775807 - 1)
		add_sign(n, p, &num);
	p->length = ft_strlen(num);
	return (num);
}
