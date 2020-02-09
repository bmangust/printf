/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_oct_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:42:41 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_base_x(uint64_t v, t_parse *p, int base)
{
	char	*s;
	char	*num;

	p->length = ft_uint_length_base(v, base);
	num = (p->zero_prec && v == 0) ? ft_strdup("") : ft_itoa_base(v, base);
	if (p->prec > p->length)
		num = add_symbols(num, '0', p->prec - p->length, 0);
	if (!p->prec && !p->zero_prec && ft_strchr(p->flags, '#') && v != 0)
		p->length += 2;
	if (!p->prec && !p->zero_prec && ft_strchr(p->flags, '0')
		&& !ft_strchr(p->flags, '-'))
		num = add_symbols(num, '0', (p->width - p->length), 0);
	if (p->type == 'p' || (ft_strchr(p->flags, '#') && v != 0))
	{
		s = num;
		num = ft_strjoin("0x", s);
		free(s);
	}
	p->type == 'X' ? num = ft_strtoupper(num, 1) : 0;
	return (num);
}

char	*print_base_o(uint64_t v, t_parse *p, int base)
{
	char	*s;
	char	*num;

	p->length = ft_uint_length_base(v, base);
	num = ft_itoa_base(v, base);
	if (p->zero_prec && v == 0 && !ft_strchr(p->flags, '#'))
		num[0] = '\0';
	if (p->zero_prec && v == 0)
		return (num);
	if (p->prec > p->length)
		num = add_symbols(num, '0', p->prec - p->length, 0);
	if (!p->prec && !p->zero_prec && ft_strchr(p->flags, '#') && v != 0)
		p->length += 1;
	if (!p->prec && !p->zero_prec && ft_strchr(p->flags, '0')
		&& !ft_strchr(p->flags, '-'))
		num = add_symbols(num, '0', (p->width - p->length), 0);
	if (ft_strchr(p->flags, '#') && p->prec <= p->length && v != 0)
	{
		s = num;
		num = ft_strjoin("0", num);
		free(s);
	}
	return (num);
}

char	*print_base_u(uint64_t v, t_parse *p, int base)
{
	if (base == 8)
		return (print_base_o(v, p, base));
	return (print_base_x(v, p, base));
}

char	*print_base(int64_t v, t_parse *p, int base)
{
	char *s;

	s = NULL;
	if (p->type == 'p')
		s = print_base_u((int64_t)v, p, base);
	else if (p->size == INT)
		s = print_base_u((unsigned int)v, p, base);
	else if (p->size == SHORT)
		s = print_base_u((unsigned short)v, p, base);
	else if (p->size == CHAR)
		s = print_base_u((unsigned char)v, p, base);
	else if (p->size == LONG || p->size == LONGLONG)
		s = print_base_u((unsigned long)v, p, base);
	return (s);
}

void	print_percentage(t_parse *p)
{
	char *s;
	char c;

	c = ft_strchr(p->flags, '0') && !ft_strchr(p->flags, '-') ? '0' : ' ';
	s = ft_charstr(p->width > 0 ? p->width : 1, c);
	if (ft_strchr(p->flags, '-'))
		s[0] = '%';
	else
		s[p->width == 0 ? 0 : p->width - 1] = '%';
	buffer(p, s, 1);
}
