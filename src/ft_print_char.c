/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/01/29 18:03:36 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(char c, t_parse *p)
{
	char *s;

	s = ft_strnew(1);
	s[0] = c;
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
