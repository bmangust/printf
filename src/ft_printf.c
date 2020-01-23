/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/01/23 20:23:45 by jbloodax         ###   ########.fr       */
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
	new->size = 0;
	new->is_signed = 0;
	new->spaces = 0;
	new->flags = NULL;
	new->width = 0;
	new->precision = 0;
	new->E = 0;
	new->printed = 0;
	new->length = 0;
	new->next = NULL;
	return (new);
}

void		clear_param(t_parse *p)
{
	if (!p)
		return ;
	free(p->flags);
	p->type = 0;
	p->size = 0;
	p->is_signed = 0;
	p->spaces = 0;
	p->flags = NULL;
	p->width = 0;
	p->E = 0;
	p->precision = 0;
	p->length = 0;
	p->next = NULL;
}

void		del_param(t_parse *p)
{
	if (!p)
		return ;
	free(p->flags);
	free(p);
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


int ft_int_length_base(int value, int base)
{
	int cnt;

	cnt = 0;
	if (value <= 0) {
		if (base == 10)
			cnt++;
	}
//	if (!value)
//		cnt++;
	while (value) {
		value /= base;
		cnt++;
	}
	return (cnt);
}


void	print_char(va_list valist, t_parse *p)
{
	char	c;

	c = (char)va_arg(valist, int);
	if (p->flags && ft_strchr(p->flags, '-'))
	{
		ft_putchar(c);
		while ((p->width)-- > 0)
		{
			ft_putchar(' ');
			p->printed++;
		}
	}
	else
	{
		while ((p->width)-- > 1)
		{
			ft_putchar(' ');
			p->printed++;
		}
		ft_putchar(c);
		p->printed++;
	}
}

void		print_str(char *temp, t_parse *p)
{
	int		len_str;
	int		i;
	int		precision;

	if (!temp)
	{
		write(1, "(null)", 6);
		p->printed += 6;
		return ;
	}


	len_str = ft_strlen(temp);
	i = 0;
	precision = p->precision;

	// printf("FLAGS: %s\n", p->flags);
	// printf("WIDTH: %d\n", p->width);
	// printf("PRECISION: %d\n", p->precision);
	// printf("LEN STR %d", len_str);



	if (ft_strchr(p->flags, '-'))
	{

		if (p->precision != 0 && p->precision <= len_str)
		{
			while ((precision)-- > 0)
			{
				ft_putchar(temp[i++]);
				p->printed++;
			}
			while ((p->width)-- > p->precision)
			{
				ft_putchar(' ');
				p->printed++;
			}
		}
		else
		{
			if (p->width < len_str)
			{
				while (i < len_str)
				{
					ft_putchar(temp[i++]);
					p->printed++;
				}
			}
			else
			{
				while (i < len_str)
				{
					ft_putchar(temp[i++]);
					p->printed++;
				}
				while (i++ < p->width)
				{
					ft_putchar(' ');
					p->printed++;
				}
			}
		}

	}
	else
	{
		if (p->precision != 0 && p->precision <= len_str)
		{
			while ((p->width)-- > p->precision)
			{
				ft_putchar(' ');
				p->printed++;
			}
			while ((precision)-- > 0)
			{
				ft_putchar(temp[i++]);
				p->printed++;
			}

		} else {
			if (p->width < len_str) {
				while (i < len_str) {
					ft_putchar(temp[i++]);
					p->printed++;
				}
			} else {
				while ((p->width)-- > len_str) {
					ft_putchar(' ');
					p->printed++;
				}

				while (i < len_str) {
					ft_putchar(temp[i++]);
					p->printed++;
				}
			}
		}
	}
}

/*
**	printing int
*/

int		int_length_and_update(intmax_t n, t_parse *p)
{
	p->length = ft_int_length_base(n, 10);
	if (n >= 0 && ft_strchr(p->flags, '+'))
		p->length++;
	if ((n < 0 || ft_strchr(p->flags, '+')) && p->precision)
		p->precision++;
//	if (n < 0 || p->precision > p->length)
//		p->length--;
	return (p->length);
}

int     is_positive(intmax_t n, t_parse *p)
{
	if (p->size == INT)
		return ((int) n >= 0) ? 1 : 0;
	else if (p->size == LONG)
		return ((long int) n >= 0) ? 1 : 0;
	else if (p->size == LONGLONG)
		return ((long long int) n >= 0) ? 1 : 0;
	else if (p->size == SHORT)
		return ((short int) n >= 0) ? 1 : 0;
	return (0);
}

void	put_sign(intmax_t n, t_parse *p)
{
	if (!is_positive(n, p) || ft_strchr(p->flags, '+'))
	{
		if (!is_positive(n, p))
			ft_putchar('-');
		else if (ft_strchr(p->flags, '+'))
			ft_putchar('+');
		p->length -= 1;
		p->width -= 1;
		if ((!is_positive(n, p) || ft_strchr(p->flags, '+')) && p->precision)
			p->precision -= 1;
//		p->printed += 1;
	}
	else if (ft_strchr(p->flags, ' ') && p->spaces == 0)
	{
		ft_putchar(' ');
		p->printed += 1;
	}
}

void	check_size_and_print_int(intmax_t n, t_parse *p)
{
	if (p->size == INT)
		ft_putnbr(ft_absint((int) n));
	else if (p->size == LONG)
		ft_putnbr(ft_absint((long int) n));
	else if (p->size == LONGLONG)
		ft_putnbr(ft_absint((long long int) n));
	else if (p->size == SHORT)
		ft_putnbr(ft_absint((short int) n));
}

void	print_left_aligned_int(t_parse *p, int n)
{
	if (p->width > p->length && p->width > p->precision)
		p->printed += p->width;
	else
		p->printed += MAX(p->precision, p->length);
	if (ft_strchr(p->flags, ' ') && is_positive(n, p) && p->width > p->length)
	{
		p->printed -= 1;
		p->width -= 1;
	}
	put_sign(n , p);
	p->width -= MAX(p->precision, p->length);
	while ((p->precision)-- > p->length)
	{
		ft_putchar('0');
//		p->width -= 1;
	}
	check_size_and_print_int(n, p);
    while ((p->width)-- > 0)
        ft_putchar(' ');
}

void	print_int_max_width(intmax_t n, t_parse *p)
{
	p->printed += p->width;
	if (ft_strchr(p->flags, '0') && !p->precision) {
		put_sign(n, p);
		while (p->width-- > p->length)
			ft_putchar('0');
	}
	else
	{
//	    if (!is_positive(n, p))
//	        p->width--;
		while (p->width-- > (MAX(p->length, p->precision)))
			ft_putchar(' ');
		p->spaces = 1;
        if (p->precision > 0)
        {
            put_sign(n, p);
            while (p->precision-- > p->length)
                ft_putchar('0');
        }
        else //if (!ft_strchr(p->flags, '0'))
            put_sign(n, p);
    }
	check_size_and_print_int(n, p);
}

void	print_int(va_list valist, t_parse *p)
{
	intmax_t	n;

	n = va_arg(valist, intmax_t);
	int_length_and_update(n, p);
	if (ft_strchr(p->flags, '-'))
        print_left_aligned_int(p, n);
	else
	{
		if (p->width > p->precision && p->width > p->length)
			print_int_max_width(n, p);
		else
		{
			p->printed += MAX(p->length, p->precision);
			put_sign(n, p);
			while (p->precision > p->length)
			{
				ft_putchar('0');
				p->precision--;
			}
			check_size_and_print_int(n, p);
		}
	}
}

/*
**	printing oct and hex
*/

void	print_base(int value, t_parse *p, int base)
{
	char	*s;
	char	*number;

	p->length = ft_int_length_base(value, base);
	s = ft_strnew(MAX(p->precision, p->length));
	if (p->precision > p->length)
	{
		while ((p->precision)-- > p->length)
			ft_strcat(s, "0");
	}
	if (base == 8)
		number = ft_itoa_base(value, 8);
	else
		number = ((p->type == 'x') ? ft_itoa_base(value, 16) : ft_itoa_baseu(value, 16));
	ft_strcat(s, number);
	free(number);
	p->precision = 0;
	print_str(s, p);
	free(s);
}

void	print_percentage(t_parse *p)
{
	if (ft_strchr(p->flags, '-'))
	{
		ft_putchar('%');
		while (--(p->width) > 0)
			ft_putchar(' ');
	}
	else
	{
		while (--(p->width) > 0)
			ft_putchar(' ');
		ft_putchar('%');
	}
	p->printed += p->width > 0 ? p->width : 1;
}


/*
**	printing float
*/

int *get_bits(float f)
{
	int d = *((int*)&f);
	int *bits;
	int i = 32;
	bits = (int*)malloc(sizeof(int)*32);

	while(--i >= 0)
	{
		bits[i] = ((d >> i) & 1);
	}
	return (bits);
}

void print_array(int *arr, int length)
{
	while (--length >= 0)
	{
		printf("%d", arr[length]);
	}
	printf("\n");
}

long long int		float_base(double x, t_parse *p)   // DEL p
{
	double	rest;
	int		E;
	int		e;			// counter of power of 2
	long long int		base;

	E = p->E;  // change p->E (FLOAT_POWER)
	e = 0;
	rest = 1;
	base = 0;
	while (E++ < FLOAT_POWER)
	{
		rest = x / ft_pow(2, E);
		if (rest >= 1 && rest < 2)
		{
			e = E + 1;
			break ;
		}
	}
	rest = x;
	while (rest > 0 && e-- > 0)
	{
		//printf("* rest: %f\n* base: %d\n* power: %d\n", rest, base, e);
		base += ft_pow(2, e);
		rest = x - base;
		//printf("____________\n");
	}
	// printf("REST in the end: %f\n", rest);
	// printf("POWER in the end: %d\n", e);
	// printf("___________\n");
	//if (e >= 0)
		base += rest;
	//printf("BASE: %d\n", base);
	return (base);
}




void	print_float(va_list valist, t_parse *p)
{
	double	x;
	double	y;
	long long int		integer;
	long long int		fract;
	char				*str_int;
	char				*str_fract;
	char				*str;
	int					sign;

	sign = 0;
	(ft_strchr(p->flags, '+')) ? sign = 1 : sign; 

	if (!p->precision)
		p->precision = 6;
	x = va_arg(valist, double);
	integer = float_base(x, p);
	fract = float_base(((x - integer) * ft_pow(10, p->precision + 1)), p);
	
	(integer < 0 || x < 0) ? fract *= -1 : fract;
	if (fract != 0)
		fract = (fract - 5)/10 + 1;
	
	//printf("%d\n", sign);
	str_int = ft_ltoa(integer, (sign + 1));
	sign = 0;
	str_fract = ft_ltoa(fract, sign);
	str = ft_strcat(str_int, str_fract);

	
	
	
	//printf("IN:  %f\n", x);
	// printf("INTEGER: %lld\n", integer);
	// printf("FRACTIONAL:  %lld\n", fract);
	

	// printf("str int: %s\n", str_int);
	// printf("str fract: %s\n", str_fract);

	//printf("res: %s\n", str);

	p->precision = 0;

	print_str(str, p);
	
	
	
}


//	float x = 0.15625;
	int *bits;

	printf("%f\n", x);

	bits = get_bits(x);
	print_array(bits, 32);
//	printf("%d\n", get_exp(bits));

}

/*
**	prints one argument
*/

void	print_arg(t_parse *p, va_list valist)
{
	//types = "%diufFeEgGxXoscpaAn";
	if (ft_strchr("diu", p->type))
		print_int(valist, p);
	else if ('o' == p->type)
		print_base(va_arg(valist, int), p, 8);
	else if (ft_strchr("xX", p->type))
		print_base(va_arg(valist, int), p, 16);
	else if ('c' == p->type)
		print_char(valist, p);
	else if ('s' == p->type)
		print_str(va_arg(valist, char*), p);
	else if ('%' == p->type)
	{
		print_percentage(p);
	}
	else if (ft_strchr("fFgG", p->type))
		print_float(valist, p);
}

/*
**	checks size of a type, uses flags in p node
*/

void	check_size(t_parse *p, char *tmp)
{
	char	*sizes;
	int		index;

	sizes = "hlL";
	index = ft_strchrn(sizes, *tmp);
	if (ft_strchr(sizes, *tmp) == ft_strchr(sizes, *(tmp + 1)))
	{
		if (index == 0)
			p->size = CHAR;
		else if (index == 1)
			p->size = LONGLONG;
		tmp++;
	}
	else if (index == 0)
		p->size = SHORT;
	else if (index == 1)
		p->size = LONG;
}

char	*read_flags(char *tmp, t_parse *p)
{
	char *f;

	p->flags = ft_strnew(5);
	f = p->flags;
	while (ft_strchr("-+ 0#", *tmp))
	{
		if ((*(ft_strchr("-+ 0#", *tmp)) == '0') &&
			(ft_strchr("-+ 0#", *(tmp + 1)) == NULL) &&
			(ft_strchr(p->flags, '0') != NULL))
			return (--tmp);
		if (!ft_strchr(p->flags, *tmp))
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

char	*check_flag_width_and_prec(char *tmp, t_parse *p, va_list valist)
{
	if (!p->flags && ft_strchr("-+ 0#", *tmp))				//flag
		tmp = read_flags(tmp, p);
	else if (ft_atoi(tmp))    									//width
	{
		p->width = ft_atoi(tmp);
		tmp += ft_int_length_base(p->width, 10) - 1;
	} else if (*tmp == '*')
		p->width = va_arg(valist, int);
	else if (*tmp == '.')                        				//precision
	{
		if (*(tmp + 1) == '*') {
			p->precision = va_arg(valist, int);
			tmp++;
		} else if ((p->precision = ft_atoi(tmp + 1)))
			tmp += ft_int_length_base(p->precision, 10);
	}
	return (tmp);
}

t_parse	*parse_string(char *tmp, t_parse *p, va_list valist)
{
	int		stop;

	stop = 0;
	while (!stop && *tmp)
	{
		tmp = check_flag_width_and_prec(tmp, p, valist);
		if (ft_strchr("hlLzjt", *tmp))			//size
			check_size(p, tmp);
		else if (ft_strchr("%diufFeEgGxXoscpaAn", *tmp))		//type
		{
			p->type = *tmp;
			p->next = tmp;
			stop = 1;
		}
		else
		{
			//ERROR PARSING
		}
		++tmp;
	}
	return (p);
}

int		ft_printf(const char *restrict s, ...)
{
	va_list	valist;
	t_parse	*p;
	char	*tmp;
	int		printed;

	tmp = (char*)s;
	va_start(valist, s);
	p = new_param();
	while (*tmp)
	{
		if (*tmp != '%')
		{
			ft_putchar(*tmp);
			p->printed++;
		}
		else
		{
			tmp++;
			parse_string(tmp, p, valist);
			tmp = p->next;
			print_arg(p, valist);
			clear_param(p);
		}
		tmp++;
	}
	printed = p->printed;
	del_param(p);
	return (printed);
}
