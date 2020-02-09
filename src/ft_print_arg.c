/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:34:39 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:36:15 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_arg(t_parse *p)
{
	char *s;

	if (ft_strchr("diu", p->type))
		print_int((int64_t)p->arg_i, p);
	else if ('c' == p->type)
		print_char((char)p->arg_i, p);
	else if ('s' == p->type)
		print_str(p->arg_s, p);
	else if ('%' == p->type)
		print_percentage(p);
	else if (ft_strchr("fFgGeEpxXo", p->type))
	{
		if ('o' == p->type)
			s = print_base((uint64_t)p->arg_i, p, 8);
		else
			s = ft_strchr("pxX", p->type) ?
			print_base((uint64_t)p->arg_i, p, 16) : print_float(p->arg_d, p);
		print_str(s, p);
		free(s);
	}
}

void	get_and_print_arg(va_list valist, t_parse *p)
{
	if (p->type == 's')
		p->arg_s = va_arg(valist, char*);
	else if (ft_strchr("fFgGeE", p->type) && !p->size)
		p->arg_d = va_arg(valist, double);
	else if (ft_strchr("fFgGeE", p->type))
		p->arg_d = va_arg(valist, long double);
	else if (ft_strchr("xX", p->type) &&
				(p->size == LONG || p->size == LONGLONG))
		p->arg_i = va_arg(valist, unsigned long long);
	else if (p->type != '%')
		p->arg_i = va_arg(valist, int64_t);
	print_arg(p);
}

t_parse	*parse_string(char *tmp, t_parse *p, va_list valist)
{
	if (!p->flags && ft_strchr("-+ 0#", *tmp))
		tmp = read_flags(tmp, p);
	tmp = read_width(p, tmp, valist);
	if (*tmp == '.')
		tmp = read_prec(tmp + 1, p, valist);
	if (ft_strchr("hlLzjt", *tmp))
		tmp = read_size(p, tmp);
	if (ft_strchr("%diufFxXoscpgGeE", *tmp))
		read_type(tmp, p);
	else
		p->next = tmp - 1;
	get_and_print_arg(valist, p);
	return (p);
}

void	buffer(t_parse *p, char *s, int freeable)
{
	char	*tmp;

	if (!p->buf)
		p->buf = ft_strnew(0);
	if (!s)
		return ;
	p->printed += ft_strlen(s);
	tmp = p->buf;
	p->buf = ft_strjoin(p->buf, s);
	free(tmp);
	if (freeable)
		free(s);
}

char	*read_line(t_parse *p, char *s)
{
	char	*tmp;
	int		index[3];

	index[1] = ft_strchrn(s, '%');
	index[2] = ft_strchrn(s, '{');
	if (index[1] != -1 && index[2] != -1)
		index[0] = index[1] < index[2] ? index[1] : index[2];
	else
		index[0] = index[1] == -1 ? index[2] : index[1];
	if (index[1] != -1 || index[2] != -1)
	{
		tmp = ft_strsub(s, 0, index[0]);
		buffer(p, tmp, 1);
		s += index[0] - 1;
	}
	else
	{
		buffer(p, s, 0);
		s += ft_strlen(s) - 1;
	}
	return (s);
}
