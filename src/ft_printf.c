/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/01/25 21:17:31 by akraig           ###   ########.fr       */
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
	new->skip_zero = 0;
	new->printed = 0;
	new->length = 0;
	new->next = NULL;
	return (new);
}

void		clear_param(t_parse *p)
{
	if (!p)
		return ;
	p->type = 0;
	p->size = 0;
	p->is_signed = 0;
	p->spaces = 0;
	p->flags ? free(p->flags) : 0;
	p->flags = NULL;
	p->width = 0;
	p->E = 0;
	p->skip_zero = 0;
	p->precision = 0;
	p->length = 0;
	p->next = NULL;
}

void		del_param(t_parse *p, va_list valist)
{
	if (!p)
		return ;
	free(p->flags);
	free(p);
	va_end(valist);
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


void	print_char(va_list valist, t_parse *p)
{
	char	c;

	c = (char)va_arg(valist, int);
	if (p->flags && ft_strchr(p->flags, '-'))
	{
		ft_putchar(c);
		p->printed++;
		while ((p->width)-- > 1)
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

int		int_length_and_update(int64_t n, t_parse *p)
{
	p->length = p->is_signed ? ft_int_length_base(n, 10)
							: ft_uint_length_base(n, 10);
	if (p->is_signed && n >= 0 && ft_strchr(p->flags, '+'))
		p->length++;
	if ((n < 0 || ft_strchr(p->flags, '+')) && p->precision)
		p->precision++;
	return (p->length);
}

int     is_positive(int64_t n, t_parse *p)
{
	if (p->is_signed)
	{
		if (p->size == INT)
			return ((int) n >= 0) ? 1 : 0;
		if (p->size == CHAR)
			return ((char) n >= 0) ? 1 : 0;
		else if (p->size == LONG)
			return ((long int) n >= 0) ? 1 : 0;
		else if (p->size == LONGLONG)
			return ((long long int) n >= 0) ? 1 : 0;
		else if (p->size == SHORT)
			return ((short int) n >= 0) ? 1 : 0;
	}
	return (1);
}

void	put_sign(int64_t n, t_parse *p)
{
//	if (n != (-9223372036854775808))
//	{
		if (p->is_signed && (!is_positive(n, p) || ft_strchr(p->flags, '+')))
		{
			if (!is_positive(n, p))
				ft_putchar('-');
			else if (ft_strchr(p->flags, '+'))
				ft_putchar('+');
			p->length -= 1;
			p->width -= 1;
			if ((!is_positive(n, p) || ft_strchr(p->flags, '+')) && p->precision)
				p->precision -= 1;
		}
		else if (p->is_signed && ft_strchr(p->flags, ' ') && p->spaces == 0)
		{
			ft_putchar(' ');
			p->printed += 1;
		}
//	}
}

void	check_size_and_print_int(int64_t n, t_parse *p)
{
	if (p->is_signed && (n != 0 || p->skip_zero == 0))		//(n != 0 || (p->width != -100 && p->precision != -100))
	{
		if (p->size == INT)
			ft_putnbr(ft_absint((int) n));
		else if (p->size == CHAR)
			ft_putnbr(ft_absint((char) n));
		else if (p->size == LONG)
			ft_putnbr(ft_absint((long int) n));
		else if (p->size == LONGLONG)
			ft_putnbr(ft_absint((long long int) n));
		else if (p->size == SHORT)
			ft_putnbr(ft_absint((short int) n));
	}
	else if (n != 0 || p->skip_zero == 0)					//(n != 0 || (p->width != -100 && p->precision != -100))
	{
		if (p->size == INT)
			ft_unsigned_putnbr((unsigned int) n);
		else if (p->size == CHAR)
			ft_putnbr(ft_absint((unsigned char) n));
		else if (p->size == LONG)
			ft_unsigned_putnbr((unsigned long) n);
		else if (p->size == LONGLONG)
			ft_unsigned_putnbr((unsigned long long int) n);
		else if (p->size == SHORT)
			ft_unsigned_putnbr((unsigned short int) n);
	}
	else
		p->printed--;
}



void	print_left_aligned_int(t_parse *p, int64_t n)
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
	}
	check_size_and_print_int(n, p);
	while ((p->width)-- > 0)
		ft_putchar(' ');
}

void	print_int_max_width(long long n, t_parse *p)
{
	p->printed += p->width;
	if (ft_strchr(p->flags, '0') && p->skip_zero == 0) {
		put_sign(n, p);
		while (p->width > p->precision && p->precision != 0)
		{
			p->width--;
			ft_putchar(' ');
		}
		while (p->width-- > p->length)
			ft_putchar('0');
	}
	else
	{
		while (p->width-- > (MAX(p->length, p->precision)))
			ft_putchar(' ');
		p->spaces = 1;
		if (p->precision > 0)
		{
			put_sign(n, p);
			while (p->precision-- > p->length)
				ft_putchar('0');
		}
		else
			put_sign(n, p);
	}
	(n == 0 && p->skip_zero == 1) ? ft_putchar(' ') : check_size_and_print_int(n, p);
}

void	print_s_int(int64_t n, t_parse *p)
{
	if (p->size == SHORT)
		n = (short)n;
	else if (p->size == CHAR)
		n = (char)n;
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

void	print_us_int(uint64_t n, t_parse *p)
{
	if (p->size == SHORT)
		n = (unsigned short)n;
	else if (p->size == CHAR)
		n = (unsigned char)n;
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

void	print_int(va_list valist, t_parse *p)
{
	if (p->is_signed)
	{
		if (p->size == LONG || p->size == LONGLONG)
			print_s_int(va_arg(valist, int64_t), p);
		else
			print_s_int(va_arg(valist, int32_t), p);
	}
	else
	{
		if (p->size == LONG || p->size == LONGLONG)
			print_us_int(va_arg(valist, uint64_t), p);
		else
			print_us_int(va_arg(valist, uint32_t), p);
	}
}

/*
**	printing oct and hex
*/

int64_t	cast_number(int64_t v, t_parse *p)
{
	if (p->type == 'p')
		return ((int64_t) v);
	if (p->size == INT)
		return ((unsigned int)v);
	else if (p->size == SHORT)
		return ((unsigned short)v);
	else if (p->size == CHAR)
		return ((unsigned char)v);
	else if (p->size == LONG)
		return ((unsigned long)v);
	return ((unsigned long long)v);
}

char	*prepare_string(t_parse *p, int base, int v)
{
	char *s;

	p->length = ft_int_length_base(v, base);
	if (p->type == 'p' || ft_strchr(p->flags, '#'))
		p->length += (base == 8) ? 1 : 2;
	s = (ft_strchr(p->flags, '0') && !p->precision) ? ft_strnew(p->width)
						: ft_strnew(MAX(p->precision, p->length));
	if (p->type == 'p' || ft_strchr(p->flags, '#'))
	{
		if (base == 8)
			ft_strcpy(s, "0");
		else if (v != 0)
			(p->type == 'X') ? ft_strcat(s, "0X") : ft_strcat(s, "0x");
	}
	if (p->precision > p->length)
		while ((p->precision)-- > p->length)
			ft_strcat(s, "0");
	if (!p->precision && !ft_strchr(p->flags, '-') && ft_strchr(p->flags, '0'))
		while ((p->width)-- > p->length && p->width > p->precision)
			ft_strcat(s, "0");
	return (s);
}

void	print_base(uint64_t v, t_parse *p, int base)
{
	char	*s;
	char	*number;

	v = cast_number(v, p);
	s = prepare_string(p, base, v);
	if (base == 8)
		number = ft_itoa_base(v, 8);
	else
		number = ((p->type == 'X') ? ft_itoa_baseu(v, 16) : ft_itoa_base(v, 16));
	if (p->skip_zero && v == 0)
		number[ft_strlen(number) - 1] = '\0';
	ft_strcat(s, number);
	free(number);
	p->precision = 0;
	print_str(s, p);
	free(s);
}

void	print_percentage(t_parse *p)
{
	p->printed += p->width > 0 ? p->width : 1;
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

long long int		float_base(double x)
{
	double	rest;
	int		E;
	int		e;			// counter of power of 2
	long long int		base;

	E = -FLOAT_POWER;
	e = 0;
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
	//char	sign;

	x = va_arg(valist, double);
	integer = float_base(x);
	y = ((x - (double) integer) * (double) ft_pow(10, p->precision));
	printf("y = %f\n", y);
	fract = float_base(y);
	(integer < 0 || x < 0) ? fract *= -1 : fract;


	printf("x: %f\n", x);
	printf("INTEGER: %lld\n", integer);
	printf("FRACTIONAL: %lld\n", fract);


//	float x = 0.15625;
	int *bits;

	printf("%f\n", x);

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
		print_base(va_arg(valist, uint64_t), p, 8);
	else if (ft_strchr("pxX", p->type))
		print_base(va_arg(valist, uint64_t), p, 16);
	else if ('c' == p->type)
		print_char(valist, p);
	else if ('s' == p->type)
		print_str(va_arg(valist, char*), p);
	else if ('%' == p->type)
		print_percentage(p);
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

	sizes = "hlLzt";
	index = ft_strchr(sizes, *tmp);
	if (ft_strchr(sizes, *tmp) == ft_strchr(sizes, *(tmp + 1)))
	{
		if (index == 0)
			index = 5;
		else if (index == 1)
			index = 6;
	}
	if (index == 0)
		p->size = SHORT;
	else if (index == 1)
		p->size = LONG;
	else if (index == 2 || index == 3 || index == 4 || index == 6)
		p->size = LONGLONG;
	else if (index == 5)
		p->size = CHAR;
	p->next = (index == 5 || index == 6) ? tmp + 2 : tmp + 1;
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
			return (tmp);
		if (!ft_strchr(p->flags, *tmp))
		{
			*f = *tmp;
			f++;
		}
		tmp++;
	}
	return (tmp);
}

/*
**	parses string till type indetifier,
**	returns list node with all parameters and pointer to next symbol
*/

char	*check_flag_width_and_prec(char *tmp, t_parse *p, va_list valist)
{
	if (!p->flags && ft_strchr("-+ 0#", *tmp))				//flag
		tmp = read_flags(tmp, p);
	if (*tmp >= '0' && *tmp  <= '9')    									//width
	{
		(*tmp >= '0' && *tmp  <= '9') ? p->width = ft_atoi(tmp) : 0; 	//replaced (p->skip_zero = 1) for 0
		tmp += *tmp >= '0' ? ft_int_length_base(p->width, 10) + 1
					: ft_int_length_base(p->width, 10);
	}
	else if (*tmp == '*')
		p->width = va_arg(valist, int);
	if (*tmp == '.')                        				//precision
	{
		if (*(tmp + 1) == '*')
		{
			p->precision = va_arg(valist, int);
			tmp++;
		}
		else if (*(tmp + 1) >= '0' && *(tmp + 1) <= '9')
		{
			(ft_atoi(tmp + 1) == 0) ? (p->skip_zero = 1)
			        : (p->precision = ft_atoi(tmp + 1));
			tmp += ft_int_length_base(p->precision, 10) + 1;
		}
		else
			p->skip_zero = 1;
	}
	return (tmp);
}

t_parse	*parse_string(char *tmp, t_parse *p, va_list valist)
{
    tmp = check_flag_width_and_prec(tmp, p, valist);
    if (ft_strchr("hlLzjt", *tmp))			//size
    {
        check_size(p, tmp);
        tmp = p->next;
    }
    if (ft_strchr("%diufFxXoscp", *tmp))		//type diufFeEgGxXoscpaAn
    {
        if ((*tmp == 'd' || *tmp == 'i') && !ft_strchr("tz", p->size))              //difFeExXo
            p->is_signed = 1;
        p->type = *tmp;
        p->next = tmp;
    }
    else
    {
        clear_param(p);
        return (NULL);
    }
	return (p);
}

int		ft_printf(const char *restrict s, ...)
{
	va_list	valist;
	t_parse	*p;
	int		printed;

	va_start(valist, s);
	p = new_param();
	while (*s)
	{
		if (*s != '%')
		{
			ft_putchar(*s);
			p->printed++;
		}
		else
		{
			s++;
			parse_string((char *)s, p, valist);
			if (!p->next)
			    return (-1);
			s = p->next;
			print_arg(p, valist);
			clear_param(p);
		}
		s++;
	}
	printed = p->printed;
	del_param(p, valist);
	return (printed);
}
