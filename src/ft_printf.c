/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/01/29 20:30:55 by akraig           ###   ########.fr       */
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
	new->skip_zero = 0;
	new->printed = 0;
	new->length = 0;
	new->skip_0_flag = 0;
	new->E = 0;
	new->next = NULL;
	new->buf = NULL;
	new->arg_i = 0;
	new->arg_d = 0;
	new->arg_s = NULL;
	return (new);
}

void		clear_param(t_parse *p)
{
	if (!p)
		return ;
//	p->type = 0;
	p->size = 0;
//	p->is_signed = 0;
	p->spaces = 0;
	p->flags ? free(p->flags) : 0;
	p->flags = NULL;
	p->width = 0;
	p->skip_zero = 0;
	p->precision = 0;
	p->length = 0;
	p->skip_0_flag = 0;
	p->E = 0;
	p->next = NULL;
//	p->arg_i = 0;
//	p->arg_d = 0;
//	p->arg_s = NULL;
}

void		del_param(t_parse *p, va_list valist)
{
	if (!p)
		return ;
	if (p->flags)
		free(p->flags);
	if (p->buf)
		free(p->buf);
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



/*
**	printing int
*/

int		int_length_and_update(int64_t n, t_parse *p)
{
	p->length = ft_int_length_base(n, 10);
	if (n < 0)
		p->length--;
	return (p->length);
}

int     is_positive(int64_t n, t_parse *p)
{
	if (p->is_signed)
		return (n >= 0) ? 1 : 0;
	return (1);
}

void	add_sign(int64_t n, t_parse *p, char **num)
{
	char *tmp;

	tmp = *num;
	if (p->is_signed && (!is_positive(n, p) || ft_strchr(p->flags, '+')))
	{
		if (!is_positive(n, p))
			*num = ft_strjoin("-", *num);
		else if (ft_strchr(p->flags, '+'))
			*num = ft_strjoin("+", *num);
		free(tmp);
	}
	else if (p->is_signed && ft_strchr(p->flags, ' ') && p->spaces == 0)
	{
		*num = ft_strjoin(" ", *num);
		free(tmp);
	}
}

void	check_size_and_print_int(int64_t n, t_parse *p)
{
	if (n == 0 && p->skip_zero == 1)
		p->printed--;															//not sure
	else
		buffer(p, ft_itoa(ft_absint(n)), 1);
}

char    *fill_width(t_parse *p, char *num, char sign)
{
	char	*spaces;
	char	*tmp;
	int		num_of_spaces;
	if (p->width > p->length)
	{
		num_of_spaces = (sign && !ft_strchr(p->flags, '-'))
		        ? p->width - p->length + 1 : p->width - p->length;
		spaces = ft_strnew(num_of_spaces);
		(p->skip_0_flag == 0 && !ft_strchr(p->flags, '-')
        && ft_strchr(p->flags, '0')) ? ft_memset(spaces, '0', num_of_spaces)
                                : ft_memset(spaces, ' ', num_of_spaces);
		if (sign && spaces[0] == ' ' && !ft_strchr(p->flags, '-'))
			spaces[p->width - p->length] = sign;
		else if (sign && !ft_strchr(p->flags, '-'))
			spaces[0] = sign;
		if (ft_strchr(p->flags, '-'))
			tmp = ft_strjoin(num, spaces);
		else
			tmp = ft_strjoin(spaces, num);
		free(num);
		free(spaces);
		return (tmp);
	}
	return (num);
}


char	*get_int(t_parse *p, int64_t n)
{
	char *zeroes;
	char *tmp;
	char *num;

	if (n == 0 && p->skip_zero == 1)
		return (ft_strdup(""));
	num = ft_itoa(ft_absint(n));
	if (p->precision > p->length)
	{
		zeroes = ft_strnew(ft_absint(p->precision - p->length));
		ft_memset(zeroes, '0', p->precision - p->length);
		tmp = num;
		num = ft_strjoin(zeroes, num);
		free(tmp);
		free(zeroes);
	}
	add_sign(n, p, &num);
	p->length = ft_strlen(num);
	return (num);
}

void	print_s_int(int64_t n, t_parse *p)
{
	char	*num;
	char	sign;
	char	*tmp;

	sign = 0;
	int_length_and_update(n, p);
	num = get_int(p, n);
	if (num[0] ==  '-' || num[0] == '+' || num[0] == ' ')
		sign = num[0];
	tmp = sign && !ft_strchr(p->flags, '-')
	        ? ft_strsub(num, 1, ft_strlen(num) - 1) : ft_strdup(num);
	free(num);
	tmp = fill_width(p, tmp, sign);
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
			print_s_int((unsigned int) n, p);
		else if (p->size == CHAR)
			print_s_int((unsigned char) n, p);
		else if (p->size == LONG)
			print_s_int((unsigned long) n, p);
		else if (p->size == LONGLONG)
			print_s_int((unsigned long long int) n, p);
		else if (p->size == SHORT)
			print_s_int((unsigned short int) n, p);
	}
}

/*
**	printing oct and hex
*/

char	*prepare_string(t_parse *p, int base, int64_t v)
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
	p->length = ft_strlen(s);
	p->precision = 0;
	s = fill_width(p, s, 0);
	buffer(p, s, 1);
}

void	print_percentage(t_parse *p)
{
	char *s;

	s = ft_strnew(p->width > 0 ? p->width : 1);
	ft_memset(s, ' ', p->width > 0 ? p->width : 1);
	;
	if (ft_strchr(p->flags, '-'))
		s[0] = '%';
	else
		s[p->width == 0 ? 0 : p->width - 1] = '%';
	buffer(p, s, 1);
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

/*
**	prints one argument
*/

void	print_arg(t_parse *p)
{
	if (ft_strchr("diu", p->type))
		print_int((int64_t)p->arg_i, p);
	else if ('o' == p->type)
		print_base((uint64_t)p->arg_i, p, 8);
	else if (ft_strchr("pxX", p->type))
		print_base((uint64_t)p->arg_i, p, 16);
	else if ('c' == p->type)
		print_char((char)p->arg_i, p);
	else if ('s' == p->type)
		print_str(p->arg_s, p);
	else if ('%' == p->type)
		print_percentage(p);
	else if (ft_strchr("fFgG", p->type))
		print_float(p->arg_d, p);
}

/*
**	checks size of a type, uses flags in p node
*/

char    *read_width(t_parse *p, char *tmp, va_list valist)
{
    if (*tmp >= '0' && *tmp  <= '9')    										//width
    {
        (*tmp >= '0' && *tmp  <= '9') ? p->width = ft_atoi(tmp) : 0;
        tmp += ft_int_length_base(p->width, 10);
    }
    else if (*tmp == '*')
    {
        p->width = va_arg(valist, int);
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

char	*read_precision(char *tmp, t_parse *p, va_list valist)
{
	p->skip_0_flag = 1;
	if (*(tmp + 1) == '*')
	{
		p->precision = va_arg(valist, int);
		tmp += 2;
	}
	else if (*(tmp + 1) >= '0' && *(tmp + 1) <= '9')
	{
		(ft_atoi(tmp + 1) == 0) ? (p->skip_zero = 1)
								: (p->precision = ft_atoi(tmp + 1));
		tmp += ft_int_length_base(p->precision, 10) + 1;
	}
	else
	{
		p->skip_zero = 1;
		tmp++;
	}
	return (tmp);
}

void	read_type(char *tmp, t_parse *p)
{
    p->is_signed = 0;
    p->type = *tmp;
    p->next = tmp;
    if ((*tmp == 'd' || *tmp == 'i') && !ft_strchr("tz", p->size))			//difFeExXo
        p->is_signed = 1;
}

void    get_and_print_arg(va_list valist, t_parse *p)
{
    if (p->type == 's')
        p->arg_s = va_arg(valist, char*);
    else if (p->type == 'f' || p->type == 'F')
        p->arg_d = va_arg(valist, double);
    else
        p->arg_i = va_arg(valist, int64_t);
    print_arg(p);
}

/*
**	parses string till type indetifier,
**	returns list node with all parameters and pointer to next symbol
*/

t_parse	*parse_string(char *tmp, t_parse *p, va_list valist)
{
	if (!p->flags && ft_strchr("-+ 0#", *tmp))								//flag
		tmp = read_flags(tmp, p);
    tmp = read_width(p, tmp, valist);
	if (*tmp == '.')                        									//precision
		tmp = read_precision(tmp, p, valist);
    if (ft_strchr("hlLzjt", *tmp))											//size
		tmp = read_size(p, tmp);
    if (ft_strchr("%diufFxXoscp", *tmp))									//type diufFeEgGxXoscpaAn
		read_type(tmp, p);
    else
    	p->next = tmp - 1;
    get_and_print_arg(valist, p);
	return (p);
}

/*
**	weird behavior, can't concatenate string with hex number
**	sometimes catches segfault. With debugger everything is great
*/

void	buffer(t_parse *p, char *s, int freeable)
{
	char	*tmp;

	if (!p->buf)
		p->buf = ft_strnew(0);
	if (!s)
		return ;
	p->printed += ft_strlen(s);
	tmp = p->buf;
	p->buf = ft_strjoin(p->buf, s);
	free(tmp);
	if (freeable)
		free(s);
}

char	*read_line(t_parse *p, char *s)
{
	char	*tmp;
	int 	index;

	index = ft_strchrn(s, '%');
	if (index != -1)
	{
		tmp = ft_strsub(s, 0, index);
		buffer(p, tmp, 1);
		s += index - 1;
	}
	else
	{
		buffer(p, s, 0);
		s += ft_strlen(s) - 1;
	}
	return (s);
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
			s = read_line(p, (char *)s);
		else
		{
			parse_string((char *)++s, p, valist);
			if (!p->next)
			    return (-1);
			s = p->next;
			clear_param(p);
		}
		s++;
	}
	ft_putstr(p->buf);
	printed = p->printed;
	del_param(p, valist);
	return (printed);
}
