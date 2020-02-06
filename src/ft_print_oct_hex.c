/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_oct_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/01/31 16:14:34 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	printing oct and hex
*/

char	*prepare_string(t_parse *p, int base, int64_t v)
{
	char *s;

	p->length = ft_int_length_base(v, base);
	if (p->type == 'p' || ft_strchr(p->flags, '#'))
		p->length += (base == 8) ? 1 : 2;
	s = (ft_strchr(p->flags, '0') && !p->prec) ? ft_strnew(p->width)
						: ft_strnew(MAX(p->prec, p->length));
	if (p->type == 'p' || ft_strchr(p->flags, '#'))
	{
		if (base == 8)
			ft_strcpy(s, "0");
		else if (v != 0)
			(p->type == 'X') ? ft_strcat(s, "0X") : ft_strcat(s, "0x");
	}
	if (p->prec > p->length)
		while ((p->prec)-- > p->length)
			ft_strcat(s, "0");
	if (!p->prec && !ft_strchr(p->flags, '-') && ft_strchr(p->flags, '0'))
		while ((p->width)-- > p->length && p->width > p->prec)
			ft_strcat(s, "0");
	return (s);
}

void	print_base_u(uint64_t v, t_parse *p, int base)
{
	char	*s;
	char	*number;

	s = prepare_string(p, base, v);
	if (base == 8)
		number = ft_itoa_baseu(v, 8);
	else
		number = ((p->type == 'X') ? ft_itoa_baseu(v, 16) :
										ft_itoa_base(v, 16));
	if (p->zero_prec && v == 0)
		number[ft_strlen(number) - 1] = '\0';
	ft_strcat(s, number);
	free(number);
	p->length = ft_strlen(s);
	p->prec = 0;
	s = fill_width(p, s, 0);
	buffer(p, s, 1);
}

int64_t	print_base(int64_t v, t_parse *p, int base)
{
	if (p->type == 'p')
		print_base_u((int64_t) v, p, base);
	if (p->size == INT)
		print_base_u((unsigned int)v, p, base);
	else if (p->size == SHORT)
		print_base_u((unsigned short)v, p, base);
	else if (p->size == CHAR)
		print_base_u((unsigned char)v, p, base);
	else if (p->size == LONG || p->size == LONGLONG)
		print_base_u((unsigned long)v, p, base);
	return ((unsigned long long)v);
}

void	print_percentage(t_parse *p)
{
	char *s;
	char c;

	c = ft_strchr(p->flags, '0') ? '0' : ' ';
	s = ft_strnew(p->width > 0 ? p->width : 1);
	ft_memset(s, c, p->width > 0 ? p->width : 1);
	if (ft_strchr(p->flags, '-'))
		s[0] = '%';
	else
		s[p->width == 0 ? 0 : p->width - 1] = '%';
	buffer(p, s, 1);
}
