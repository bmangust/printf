/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:36:33 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:36:39 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(char c, t_parse *p)
{
	char *s;

	s = ft_strnew(1);
	s[0] = c == '\x00' ? '\x00' : c;
	if (c == 0)
		p->printed++;
	if (p->flags && ft_strchr(p->flags, '-'))
	{
		buffer(p, s, 1);
		buffer(p, ft_charstr(p->width - 1, ' '), 1);
	}
	else
	{
		buffer(p, ft_charstr(p->width - 1, ' '), 1);
		buffer(p, s, 1);
	}
}
