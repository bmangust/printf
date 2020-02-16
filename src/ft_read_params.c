/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:32:09 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	checks size of a type, uses flags in p node
*/

char	*read_width(t_parse *p, char *tmp, va_list valist)
{
	if (*tmp >= '0' && *tmp <= '9')
	{
		tmp += *tmp == '0' && ft_atoi(tmp) ? 1 : 0;
		(*tmp >= '0' && *tmp <= '9') ? p->width = ft_atoi(tmp) : 0;
		tmp += ft_int_length_base(p->width, 10);
	}
	else if (*tmp == '*')
	{
		p->width = va_arg(valist, int);
		if (p->width < 0)
		{
			p->width = -p->width;
			p->flags = p->flags ? ft_strcat(p->flags, "-") : ft_strdup("-");
		}
		tmp++;
	}
	return (tmp);
}

char	*read_size(t_parse *p, char *tmp)
{
	char	*sizes;
	int		index;

	sizes = "hlLzjt";
	index = ft_strchrn(sizes, *tmp);
	if (ft_strchr(sizes, *tmp) == ft_strchr(sizes, *(tmp + 1)))
	{
		if (index == 0)
			index = 50;
		else if (index == 1)
			index = 100;
	}
	if (index == 0)
		p->size = SHORT;
	else if (index == 1 || index == 5)
		p->size = LONG;
	else if (index == 2 || index == 3 || index == 4 || index == 100)
		p->size = LONGLONG;
	else if (index == 50)
		p->size = CHAR;
	return ((index == 50 || index == 100) ? tmp + 2 : tmp + 1);
}

char	*read_flags(char *tmp, t_parse *p)
{
	int i;

	p->flags = ft_strnew(5);
	i = 0;
	while (ft_strchr("-+ 0#", *tmp))
	{
		if ((*(ft_strchr("-+ 0#", *tmp)) == '0') &&
			(ft_strchr("-+ 0#", *(tmp + 1)) == NULL) &&
			(ft_strchr(p->flags, '0') != NULL))
			return (tmp);
		if (!ft_strchr(p->flags, *tmp))
			p->flags[i++] = *tmp;
		tmp++;
	}
	ft_strchr(p->flags, '-') ? p->skip_0_flag = 1 : 0;
	return (tmp);
}

char	*read_prec(char *tmp, t_parse *p, va_list valist)
{
	p->skip_0_flag = 1;
	if (*tmp == '*')
	{
		p->prec = va_arg(valist, int);
		tmp++;
	}
	else if (*tmp >= '0' && *tmp <= '9')
	{
		(ft_atoi(tmp) == 0) ? (p->zero_prec = 1)
								: (p->prec = ft_atoi(tmp));
		while (*tmp >= '0' && *tmp <= '9')
			tmp++;
	}
	else
		p->zero_prec = 1;
	return (tmp);
}

void	read_type(char *tmp, t_parse *p)
{
	p->is_signed = 0;
	p->type = *tmp;
	p->next = tmp;
	if ((*tmp == 'd' || *tmp == 'i') && !ft_strchr("tz", p->size))
		p->is_signed = 1;
}
