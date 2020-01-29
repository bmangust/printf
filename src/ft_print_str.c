/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/01/29 17:55:05 by jbloodax         ###   ########.fr       */
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

char	*print_str2(char *str, t_parse *p, char *temp_str, char *temp_space)
{
	char	*out;
	int		len_str;

	len_str = ft_strlen(str);
	if (!str)
		return (ft_strdup("(null)"));
	if (len_str == 0)
		out = ft_charstr(p->width, ' ');
	if (temp_str != 0 && temp_space != 0)
	{
		if (ft_strchr(p->flags, '-'))
			out = ft_strjoin(temp_str, temp_space);
		else
			out = ft_strjoin(temp_space, temp_str);
		ft_strdel(&temp_str);
		ft_strdel(&temp_space);
	}
	else
		out = ft_strdup(str);
	return (out);
}

void	print_str(char *str, t_parse *p)
{
	int		len_str;
	char	*temp_str;
	char	*temp_space;
	char	*out;

	temp_space = NULL;
	len_str = ft_strlen(str);
	temp_str = ft_strdup(str);
	if (p->precision != 0 && p->precision < len_str)
	{
		free(temp_str);
		temp_str = ft_strnew((size_t)p->precision);
		ft_strncpy(temp_str, str, (size_t)p->precision);
		len_str = p->precision;
		if (!p->width)
			out = temp_str;
	}
	if (!p->width)
		temp_space = ft_strdup("");
	if (p->width > len_str)
		temp_space = ft_charstr((p->width - len_str), ' ');
	out = print_str2(str, p, temp_str, temp_space);
	buffer(p, out, 1);
}
