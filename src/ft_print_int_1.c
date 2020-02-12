/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:44:55 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_s_int(int64_t n, t_parse *p)
{
	char	*num;
	char	sign;
	char	*tmp;

	sign = 0;
	int_length_and_update(n, p);
	num = get_int(p, n);
	if (num[0] == '-' || num[0] == '+' || num[0] == ' ')
		sign = num[0];
	if (p->width > ft_max(p->prec, p->length))
	{
		tmp = sign && !ft_strchr(p->flags, '-')
			? ft_strsub(num, 1, ft_strlen(num) - 1) : ft_strdup(num);
		free(num);
		tmp = fill_width(p, tmp, sign);
	}
	else
		tmp = fill_width(p, num, sign);
	buffer(p, tmp, 1);
}

void	print_int(int64_t n, t_parse *p)
{
	if (p->is_signed)
	{
		if (p->size == INT)
			print_s_int((int)n, p);
		else if (p->size == CHAR)
			print_s_int((char)n, p);
		else if (p->size == LONG)
			print_s_int((long int)n, p);
		else if (p->size == LONGLONG)
			print_s_int((long long int)n, p);
		else if (p->size == SHORT)
			print_s_int((short int)n, p);
	}
	else
	{
		if (p->size == INT)
			print_s_int((unsigned int)n, p);
		else if (p->size == CHAR)
			print_s_int((unsigned char)n, p);
		else if (p->size == LONG || p->size == LONGLONG)
			print_s_int((uint64_t)n, p);
		else if (p->size == SHORT)
			print_s_int((unsigned short int)n, p);
	}
}
