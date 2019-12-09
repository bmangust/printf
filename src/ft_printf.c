/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2019/12/08 21:27:58 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_node		*new_piece(char type, int mod)
{
	t_node	*new;

	if (!(new = (t_node*)malloc(sizeof(t_node))))
		return (NULL);
	new->mod = mod;
	new->type = type;
	new->s = NULL;
	new->c = 0;
	new->n = 0;
	new->f = 0;
	new->next = new;
	new->prev = new;
	return (new);
}

t_parse		*new_param(void)
{
	t_parse	*new;

	if (!(new = (t_parse*)malloc(sizeof(t_parse))))
		return (NULL);
	new->type = 0;
	new->is_signed = 0;
	new->is_long = 0;
	new->is_longlong = 0;
	new->is_short = 0;
	new->is__int64 = 0;
	new->is_size_t = 0;
	new->is_intmax_t = 0;
	new->is_ptrdiff_t = 0;
	new->flags = NULL;
	new->width = 0;
	new->width_param = 0;
	new->precision = 0;
	new->precision_param = 0;
	new->align = 0;
	new->next = NULL;
	return (new);
}

void		del_param(t_parse *param)
{
	if (!param)
		return ;
	free(param);
}

t_node		*add_last_piece(t_node **head, t_node *new)
{
	t_node *tmp;

	if (head && new)
	{
		if (*head)
		{
			tmp = (*head)->prev;
			new->next = tmp->next;
			new->next->prev = new;
			new->prev = tmp;
			tmp->next = new;
		}
		else
			*head = new;
		return (new);
	}
	return (NULL);
}

int			int_length(int n)
{
	int length;

	length = 0;
	if (n < 0)
		++length;
	while (n)
	{
		n /= 10;
		++length;
	}
	return (length);
}

//void	select_flag_int(va_list valist, t_parse *params)
//{
//	char *f;
//
//	params->flags = ft_strnew(5);
//	f = params->flags;
//	while (ft_strchr("-+ 0#", *tmp))
//	{
//		*f = *tmp;
//		f++;
//		tmp++;
//	}
//}

void	check_plus_flag_and_print(t_parse *params, int n, int len)
{
	if (params->flags && ft_strchr(params->flags, '+') && n >= 0)
	{
		ft_putchar('+');
		ft_putnbr(n);
		params->width -= (len + 1);
		return ;
	}
	if (!params->flags)
		ft_putchar(' ');
	ft_putnbr(n);
	params->width -= len;
}

void	print_int(va_list valist, t_parse *params)
{
	int		n;
	int		len;

	n = va_arg(valist, int);
	len = int_length(n);
	if (params->width_param)
		len = va_arg(valist, int);
	if (params->flags && ft_strchr(params->flags, '-'))
	{
		check_plus_flag_and_print(params, n, len);
		while ((params->width)-- > 0)
			ft_putchar(' ');
	}
	else
	{
		while (--(params->width) > len)
			ft_putchar(' ');			//need to add '0' or ' ' filler selector here
		check_plus_flag_and_print(params, n, len);
	}
}

void	print_float(va_list valist, t_parse *params)
{
	(void) valist;
	(void) params;
}

/*
**	prints one argument
*/

void	print_arg(t_parse *params, va_list valist)
{
	//types = "%diufFeEgGxXoscpaAn";
	if (ft_strchr("diuxX", params->type))
		print_int(valist, params);
		// ft_putnbr(va_arg(valist, int));
	else if ('c' == params->type)
		ft_putchar((char)va_arg(valist, int));
	else if ('s' == params->type)
		ft_putstr(va_arg(valist, char*));
	else if ('%' == params->type)
		ft_putchar('%');
	else if (ft_strchr("fFgG", params->type))
		print_float(valist, params);
}

/*
**	checks size of a type, uses flags in params node
*/

void	check_size(t_parse *params, char *tmp)
{
	char	*sizes;
	int		index;

	sizes = "hlLzjt";
	index = ft_strchrn(sizes, *tmp);
	if (ft_strchr(sizes, *tmp) == ft_strchr(sizes, *(tmp + 1)))
	{
		if (index == 0)
			params->is_signed = 1;
		else if (index == 1)
			params->is_longlong = 1;
		tmp++;
	}
	else if (index == 0)
		params->is_short = 1;
	else if (index == 1)
		params->is_long = 1;
	else if (index == 2)
		params->is__int64 = 1;
	else if (index == 3)
		params->is_size_t = 1;
	else if (index == 4)
		params->is_intmax_t = 1;
	else if (index == 5)
		params->is_ptrdiff_t = 1;
}

/*
**	complex if check needs in this situation:
**	printf(">%0+0+0d<", 4); where '0+0+' - flags, 0 - width
*/

char	*read_flags(char *tmp, t_parse *params)
{
	char *f;

	params->flags = ft_strnew(5);
	f = params->flags;
	while (ft_strchr("-+ 0#", *tmp))
	{
		if ((*(ft_strchr("-+ 0#", *tmp)) == '0') &&
			(ft_strchr("-+ 0#", *(tmp + 1)) == NULL) &&
			(ft_strchr(params->flags, '0') != NULL))
			return (--tmp);
		*f = *tmp;
		f++;
		tmp++;
	}
	return (--tmp);
}

/*
**	parses string till type indetifier,
**	returs list node with all parameters and pointer to next symbol
*/

t_parse	*parse_string(char *tmp, t_parse *params, va_list valist)
{
	int		stop;

	stop = 0;
	while (!stop && *tmp)
	{
		// printf("\n==parse stinrg==\nstart: %c\n", tmp[0]);
		if (ft_strchr("-+ 0#", *tmp))				//flag
			tmp = read_flags(tmp, params);
		else if (ft_atoi(tmp))	//width
		{
			params->width = ft_atoi(tmp);
			tmp += int_length(params->width) - 1;	//not sure, check
		}
		else if (*tmp == '*')
			params->width = va_arg(valist, int);				//add parameter here
		else if (*tmp == '.')						//precision
		{
			params->precision = ft_atoi(++tmp);
			if (*tmp == '*')
				params->precision_param = 1;		//add parameter here
			else if (params->precision != 0)
				tmp += int_length(params->precision) - 1;
		}
		else if (ft_strchr("hlLzjt", *tmp))			//size
			check_size(params, tmp);
		else if (ft_strchr("%diufFeEgGxXoscpaAn", *tmp))		//type
		{
			params->type = *tmp;
			params->next = tmp;
			stop = 1;
		}
		// printf("\n=params=\nwidth: %d\nflag: %c\n", params->width, params->flags);
		++tmp;
	}
	return (params);
}

int		ft_printf(const char *restrict s, ...)
{
	va_list	valist;
	t_parse	*params;
	char	*tmp;

	tmp = (char*)s;
	va_start(valist, s);
	while (*tmp)
	{
		if (*tmp != '%')
			ft_putchar(*tmp);
		else
		{
			tmp++;
			params = new_param();
			parse_string(tmp, params, valist);
			tmp = params->next;
			// printf("\nparams:\ntype: %c\nwidth: %d\nnext: %s\n",
			// 		params->type, params->width, params->next);
			print_arg(params, valist);
			del_param(params);
		}
		tmp++;
	}
	return (0);
}
