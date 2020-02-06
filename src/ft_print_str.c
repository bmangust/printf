/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/02/06 20:09:52 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_charstr(int size, char n)
{
	int		i;
	char	*s;

	i = 0;
	if (size <= 0)
		return (NULL);
	s = (char*)malloc((size + 1) * sizeof(char));
	if (s)
	{
		while (i < size)
		{
			s[i] = n;
			i++;
		}
		s[i] = '\0';
		return (s);
	}
	return (NULL);
}

void	print_str(char *str, t_parse *p)
{
	int		len_str;
	char	*temp_str;
	char	*out;

	if (p->type == 's' && !str)
		str = "(null)";
	len_str = ft_strlen(str);
	if (p->type == 's' && p->prec == 0 && p->zero_prec)
	{
		temp_str = ft_strdup("");
		len_str = 0;
	}
	else if (p->type == 's' && p->prec != 0 && p->prec < len_str)
	{
		temp_str = ft_strsub(str, 0, (size_t)p->prec);
		len_str = p->prec;
	}
	else if (str)
		temp_str = ft_strdup(str);
	if (ft_strchr(p->flags, '-'))
		out = add_symbols(temp_str, ' ', p->width - len_str, 1);
	else
		out = add_symbols(temp_str, ' ', p->width - len_str, 0);
	buffer(p, out, 1);
}
