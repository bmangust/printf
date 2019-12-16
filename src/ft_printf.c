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
	new->is_negative = 0;
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
	new->precision = 0;
	new->printed = 0;
	new->next = NULL;
	return (new);
}

void		clear_param(t_parse *params)
{
	if (!params)
		return ;
	free(params->flags);
	params->type = 0;
	params->is_negative = 0;
	params->is_signed = 0;
	params->is_long = 0;
	params->is_longlong = 0;
	params->is_short = 0;
	params->is__int64 = 0;
	params->is_size_t = 0;
	params->is_intmax_t = 0;
	params->is_ptrdiff_t = 0;
	params->flags = NULL;
	params->width = 0;
	params->precision = 0;
	params->next = NULL;
}

void		del_param(t_parse *params)
{
	if (!params)
		return ;
	free(params->flags);
	free(params);
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

void	print_char(va_list valist, t_parse *params)
{
	char	c;

	c = (char)va_arg(valist, int);
	if (params->flags && ft_strchr(params->flags, '-'))
	{
		ft_putchar(c);
		while ((params->width)-- > 0)
		{
			ft_putchar(' ');
			params->printed++;
		}
	}
	else
	{
		while ((params->width)-- > 1)
		{
			ft_putchar(' ');
			params->printed++;
		}
		ft_putchar(c);
		params->printed++;
	}
}

void		print_str(va_list valist, t_parse *params)
{
	(void) valist;
	(void) params;
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

void	check_width_and_print_int(t_parse *params, int n, int len)
{
	if (params->width > len && params->width > params->precision)
		params->printed += params->width;
	else
		params->printed += MAX(params->precision, len);
	if (n < 0 || ft_strchr(params->flags, '+'))
	{
		if (n < 0)
			ft_putchar('-');
		else
			ft_putchar('+');
		len--;
		params->width -= 1;
		params->printed++;
	}
	while ((params->precision)-- > len)
	{
		ft_putchar('0');
		params->width -= 1;
	}
	ft_putnbr(ft_absint(n));
	params->width -= len;
}

void	print_int(va_list valist, t_parse *params)
{
	int		n;
	int		len;

	n = va_arg(valist, int);
	len = int_length(n);
	if (n < 0)
		params->is_negative = 1;
	if (n < 0 && params->precision && !ft_strchr(params->flags, '-'))
		params->precision++;
	if (ft_strchr(params->flags, '-'))
	{
		check_width_and_print_int(params, n, len);
		while ((params->width)-- > 0)
			ft_putchar(' ');
	}
	else
	{
		if (params->width > params->precision && params->width > len)
		{
			params->printed += params->width;
			if (ft_strchr(params->flags, '0') && !params->precision)
			{
				if (n < 0)
					ft_putchar('-');
				else if (ft_strchr(params->flags, '+'))
					ft_putchar('+');
				params->width--;
				params->printed++;
				n = ft_absint(n);
			}
			if (ft_strchr(params->flags, '0') && !params->precision)
			{
				if (ft_strchr(params->flags, '+') && params->is_negative)
					params->width--;
				while ((params->width) >= (MAX(len, params->precision)))
				{
					if (ft_strchr(params->flags, '0') && !params->precision)
						ft_putchar('0');
					else
						ft_putchar(' ');
					params->width--;
				}
			}
			else
			{
				while ((params->width) > (MAX(len, params->precision))) {
					if (ft_strchr(params->flags, '0') && !params->precision)
						ft_putchar('0');
					else
						ft_putchar(' ');
					params->width--;
				}
			}
			if ((!(ft_strchr(params->flags, '0') || !params->precision) &&
			(params->is_negative && ft_strchr(params->flags, '+'))) || n < 0)
			{
				if (n < 0)
					ft_putchar('-');
				else if (ft_strchr(params->flags, '+'))
					ft_putchar('+');
				params->width--;
				params->printed++;
				n = ft_absint(n);
			}
			while (params->precision > len)
			{
				params->precision--;
				ft_putchar('0');
			}
			ft_putnbr(n);
		}
		else
		{
			params->printed += MAX(len, params->precision);
			if (ft_strchr(params->flags, '+') || params->is_negative)
			{
				if (n < 0)
					ft_putchar('-');
				else if (ft_strchr(params->flags, '+'))
					ft_putchar('+');
				params->width--;
				params->printed++;
			}
			while (params->precision > len)
			{
				ft_putchar('0');
				params->precision--;
			}
			ft_putnbr(ft_absint(n));
		}
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
		print_char(valist, params);
	else if ('s' == params->type)
		print_str(valist, params);
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
		if (!ft_strchr(params->flags, *tmp))
		{
			*f = *tmp;
			f++;
		}
		tmp++;
	}
	return (--tmp);
}

/*
**	parses string till type indetifier,
**	returns list node with all parameters and pointer to next symbol
*/

t_parse	*parse_string(char *tmp, t_parse *params, va_list valist)
{
	int		stop;

	stop = 0;
	while (!stop && *tmp)
	{
		if (!params->flags && ft_strchr("-+ 0#", *tmp))				//flag
			tmp = read_flags(tmp, params);
		else if (ft_atoi(tmp))	//width
		{
			params->width = ft_atoi(tmp);
			tmp += int_length(params->width) - 1;
		}
		else if (*tmp == '*')
			params->width = va_arg(valist, int);
		else if (*tmp == '.')						//precision
		{
			if (*(tmp + 1) == '*')
			{
				params->precision = va_arg(valist, int);
				tmp++;
			}
			else if ((params->precision = ft_atoi(tmp + 1)))
				tmp += int_length(params->precision);
		}
		else if (ft_strchr("hlLzjt", *tmp))			//size
			check_size(params, tmp);
		else if (ft_strchr("%diufFeEgGxXoscpaAn", *tmp))		//type
		{
			params->type = *tmp;
			params->next = tmp;
			stop = 1;
		}
		++tmp;
	}
	return (params);
}

int		ft_printf(const char *restrict s, ...)
{
	va_list	valist;
	t_parse	*params;
	char	*tmp;
	int		printed;

	tmp = (char*)s;
	va_start(valist, s);
	params = new_param();
	while (*tmp)
	{
		if (*tmp != '%')
		{
			ft_putchar(*tmp);
			params->printed++;
		}
		else
		{
			tmp++;
			parse_string(tmp, params, valist);
			tmp = params->next;
			print_arg(params, valist);
			clear_param(params);
		}
		tmp++;
	}
	printed = params->printed;
	del_param(params);
	return (printed);
}
