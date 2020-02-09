/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_oct_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/01/31 16:14:34 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_base_u(uint64_t v, t_parse *p, int base)
{
	char	*s;
	char	*num;

	p->length = ft_uint_length_base(v, base);
	num = (p->zero_prec && v == 0) ? ft_strdup("") : ft_itoa_base(v, base);
	if (p->prec > p->length)
		num = (p->type == 'o' && ft_strchr(p->flags, '#') && v != 0) ?
			add_symbols(num, '0', (p->prec - p->length - 1), 0) :
			add_symbols(num, '0', (p->prec - p->length), 0);
	if (!p->prec && !p->zero_prec && ft_strchr(p->flags, '#'))
		p->length += (p->type == 'o') ? 1 : 2;
	if (!p->prec && !p->zero_prec &&
			ft_strchr(p->flags, '0') && !ft_strchr(p->flags, '-'))
		num = add_symbols(num, '0', (p->width - p->length), 0);
	if (p->type == 'p' || ft_strchr(p->flags, '#'))
	{
		s = num;
		num = (base == 8) ? ft_strjoin("0", num) : ft_strjoin("0x", s);
		free(s);
	}
	(v == 0 && base == 8) ? num[ft_strlen(num) - 1] = '\0' : 0;
	p->type == 'X' ? num = ft_strtoupper(num, 1) : 0;
	return (num);
}

char	*print_base(int64_t v, t_parse *p, int base)
{
	char *s;

	s = NULL;
	if (p->type == 'p' && v == 0)
		s = ft_strdup("(nil)");
	else if (p->type == 'p')
		s = print_base_u((int64_t) v, p, base);
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
