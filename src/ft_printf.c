/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/02/01 21:01:31 by jbloodax         ###   ########.fr       */
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
	new->precision_zero = 0;
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
	p->type = 0;
	p->size = 0;
	p->is_signed = 0;
	p->spaces = 0;
	p->flags ? free(p->flags) : 0;
	p->flags = NULL;
	p->width = 0;
	p->skip_zero = 0;
	p->precision = 0;
	p->length = 0;
	p->precision_zero = 0;
	p->skip_0_flag = 0;
	p->E = 0;
	p->next = NULL;
//	p->buf = NULL;
	p->arg_i = 0;
	p->arg_d = 0;
	p->arg_s = NULL;
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

void	add_sign(int64_t n, t_parse *p, char **number)
{
	char *tmp;

	tmp = *number;
	if (p->is_signed && (!is_positive(n, p) || ft_strchr(p->flags, '+')))
	{
		if (!is_positive(n, p))
			*number = ft_strjoin("-", *number);
		else if (ft_strchr(p->flags, '+'))
			*number = ft_strjoin("+", *number);
		free(tmp);
	}
	else if (p->is_signed && ft_strchr(p->flags, ' ') && p->spaces == 0)
	{
		*number = ft_strjoin(" ", *number);
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

void	fill_width(t_parse *p, char **number)
{
	char	*spaces;
	char	*tmp;
	int		num_of_spaces;

	if (p->width > p->length)
	{
		num_of_spaces = p->width - p->length;
		spaces = ft_strnew(num_of_spaces);
		if (p->skip_0_flag == 0 && !ft_strchr(p->flags, '-') && ft_strchr(p->flags, '0'))
			ft_memset(spaces, '0', p->width - p->length);
		else
			ft_memset(spaces, ' ', p->width - p->length);
		tmp = *number;
		if (ft_strchr(p->flags, '-'))
			*number = ft_strjoin(*number, spaces);
		else
			*number = ft_strjoin(spaces, *number);
		free(tmp);
		free(spaces);
	}
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
	char *num;

	int_length_and_update(n, p);
	num = get_int(p, n);
	fill_width(p, &num);
	buffer(p, num, 1);
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
	fill_width(p, &s);
	buffer(p, s, 1);
}

void	print_percentage(t_parse *p)
{
	char *s;

	s = ft_strnew(p->width > 0 ? p->width : 1);
	ft_memset(s, ' ', p->width > 0 ? p->width : 1);
	if (ft_strchr(p->flags, '-'))
		s[0] = '%';
	else
		s[p->width - 1] = '%';
	buffer(p, s, 1);
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
	ft_strchr(p->flags, '-') ? p->skip_0_flag = 1 : 0;
	return (tmp);
}

char	*read_precision(char *tmp, t_parse *p, va_list valist)
{
	p->skip_0_flag = 1;
	if (*(tmp + 1) == '*')
	{
		p->precision = va_arg(valist, int);
		tmp++;
	}
	else if (*(tmp + 1) >= '0' && *(tmp + 1) <= '9')
	{
		(ft_atoi(tmp + 1) == 0) ? (p->skip_zero = 1)
								: (p->precision = ft_atoi(tmp + 1));
		if (*(tmp + 1) == '0' && ft_atoi((tmp + 1)) == 0)
			p->precision_zero = 1;
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
	if ((*tmp == 'd' || *tmp == 'i') && !ft_strchr("tz", p->size))			//difFeExXo
		p->is_signed = 1;
	p->type = *tmp;
	p->next = tmp;
}

/*
**	parses string till type indetifier,
**	returns list node with all parameters and pointer to next symbol
*/

t_parse	*parse_string(char *tmp, t_parse *p, va_list valist)
{
	tmp++;
	if (!p->flags && ft_strchr("-+ 0#", *tmp))								//flag
		tmp = read_flags(tmp, p);
	if (*tmp >= '0' && *tmp  <= '9')    										//width
	{
		(*tmp >= '0' && *tmp  <= '9') ? p->width = ft_atoi(tmp) : 0; 			//replaced (p->skip_zero = 1) for 0
		tmp += ft_int_length_base(p->width, 10);
	}
	else if (*tmp == '*')
		p->width = va_arg(valist, int);
	if (*tmp == '.')                        									//precision
		tmp = read_precision(tmp, p, valist);
    if (ft_strchr("hlLzjt", *tmp))											//size
		tmp = read_size(p, tmp);
    if (ft_strchr("%diufFxXoscp", *tmp))										//type diufFeEgGxXoscpaAn
		read_type(tmp, p);
    else
    	p->next = tmp - 1;
    if (p->type == 's')
    	p->arg_s = va_arg(valist, char*);
    else if (p->type == 'f' || p->type == 'F')
		p->arg_d = va_arg(valist, double);
	else
		p->arg_i = va_arg(valist, int64_t);
	print_arg(p);
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
//	printf("\n=== buffer: ===%s===\n", p->buf);
}

char	*read_line(t_parse *p, char *s)
{
	char	*tmp;
	int 	index[3];

	index[1] = ft_strchrn(s, '%');
	index[2] = ft_strchrn(s, '{');
	if (index[1] != -1 && index[2] != -1)
		index[0] = index[1] < index[2] ? index[1] : index[2];
	else
		index[0] = index[1] == -1 ? index[2] : index[1];
	if (index[1] != -1 || index[2] != -1)
	{
		tmp = ft_strsub(s, 0, index[0]);
		buffer(p, tmp, 1);
		s += index[0] - 1;
	}
	else
	{
		buffer(p, s, 0);
		s += ft_strlen(s) - 1;
	}
	return (s);
}


// /*WORKING*/


// char	*read_other(t_parse *p, char *s, int found)
// {
// 	if ((found = ft_strncmp("{DEFAULT}", s, 9)) == 0)
// 		buffer(p, "\033[0m", 0);
// 	else if ((found = ft_strncmp("{BOLDFACE}", s, 10)) == 0)
// 		buffer(p, "\033[1m", 0);
// 	else if ((found = ft_strncmp("{SEMIBRIGHT}", s, 12)) == 0)
// 		buffer(p, "\033[2m", 0);
// 	else if ((found = ft_strncmp("{INDERLINE}", s, 11)) == 0)
// 		buffer(p, "\033[4m", 0);
// 	else if ((found = ft_strncmp("{BLINK}", s, 7)) == 0)
// 		buffer(p, "\033[5m", 0);
// 	else
// 		buffer(p, "{", 0);
// 	if (found == 0)
// 		s = ft_strchr(s, '}');
// 	return (s);
// }

// char	*read_bg(t_parse *p, char *s, int found)
// {
// 	if ((found = ft_strncmp("{BLACK_BG}", s, 10)) == 0)
// 		buffer(p, "\033[40m", 0);
// 	else if ((found = ft_strncmp("{RED_BG}", s, 8)) == 0)
// 		buffer(p, "\033[41m", 0);
// 	else if ((found = ft_strncmp("{GREEN_BG}", s, 10)) == 0)
// 		buffer(p, "\033[42m", 0);
// 	else if ((found = ft_strncmp("{YELLOW_BG}", s, 11)) == 0)
// 		buffer(p, "\033[43m", 0);
// 	else if ((found = ft_strncmp("{BLUE_BG}", s, 9)) == 0)
// 		buffer(p, "\033[44m", 0);
// 	else if ((found = ft_strncmp("{MAGENTA_BG}", s, 12)) == 0)
// 		buffer(p, "\033[45m", 0);
// 	else if ((found = ft_strncmp("{CYAN_BG}", s, 9)) == 0)
// 		buffer(p, "\033[46m", 0);
// 	else if ((found = ft_strncmp("{GREY_BG}", s, 9)) == 0)
// 		buffer(p, "\033[47m", 0);
// 	else if (found != 0)
// 		s = read_other(p, s, found);
// 	if (found == 0)
// 		s = ft_strchr(s, '}');
// 	return (s);
// }

// char	*read_color(t_parse *p, char *s)
// {
// 	int	found;

// 	found = 42;
// 	if ((found = ft_strncmp("{BLACK}", s, 7)) == 0)
// 		buffer(p, "\033[30m", 0);
// 	else if ((found = ft_strncmp("{RED}", s, 5)) == 0)
// 		buffer(p, "\033[31m", 0);
// 	else if ((found = ft_strncmp("{GREEN}", s, 7)) == 0)
// 		buffer(p, "\033[32m", 0);
// 	else if ((found = ft_strncmp("{YELLOW}", s, 8)) == 0)
// 		buffer(p, "\033[33m", 0);
// 	else if ((found = ft_strncmp("{BLUE}", s, 6)) == 0)
// 		buffer(p, "\033[34m", 0);
// 	else if ((found = ft_strncmp("{MAGENTA}", s, 9)) == 0)
// 		buffer(p, "\033[35m", 0);
// 	else if ((found = ft_strncmp("{CYAN}", s, 6)) == 0)
// 		buffer(p, "\033[36m", 0);
// 	else if ((found = ft_strncmp("{GREY}", s, 6)) == 0)
// 		buffer(p, "\033[37m", 0);
// 	else if (found != 0)
// 		s = read_bg(p, s, found);
// 	if (found == 0)
// 		s = ft_strchr(s, '}');
// 	return (s);
// }









char	*read_other(t_parse *p, char *s, int found)
{
	if ((found = ft_strncmp("{DEFAULT}", s, 9)) == 0)
		buffer(p, "\033[0m", 0);
	else if ((found = ft_strncmp("{BOLDFACE}", s, 10)) == 0)
		buffer(p, "\033[1m", 0);
	else if ((found = ft_strncmp("{SEMIBRIGHT}", s, 12)) == 0)
		buffer(p, "\033[2m", 0);
	else if ((found = ft_strncmp("{ITALIC}", s, 8)) == 0)
		buffer(p, "\033[3m", 0);
	else if ((found = ft_strncmp("{INDERLINE}", s, 11)) == 0)
		buffer(p, "\033[4m", 0);
	else if ((found = ft_strncmp("{BLINK}", s, 7)) == 0)
		buffer(p, "\033[5m", 0);
	else
		buffer(p, "{", 0);
	if (found == 0)
		s = ft_strchr(s, '}');
	return (s);
}

char	**split_color(void)
{
	char	**ar;
	char	*ident;

	ident = "{BLACK,{RED,{GREEN,{YELLOW,{BLUE,{MAGENTA,{CYAN,{GREY";
	ar = ft_strsplit(ident, ',');
	return (ar);
}

char	*read_color(t_parse *p, char *s, char *code)
{
	int		found;
	char	**ar;
	int		i;

	ar = split_color();
	found = 42;
	i = -1;
	while (ar[++i] && found)
		found = ft_strncmp(ar[i], s, ft_strlen(ar[i]));
	if (!found && --i)
	{
		if (*(s + (ft_strlen(ar[i]))) == '}')
			code[3] = i + '0';
		else if ((found = ft_strncmp("_BG}", (s + (ft_strlen(ar[i]))), 4)) == 0)
		{
			code[2] = 4 + '0';
			code[3] = i + '0';
		}
		buffer(p, code, 1);
		s = ft_strchr(s, '}');
	}
	else if (found != 0)
 		s = read_other(p, s, found);
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
		if (*s != '%' && *s != '{')
			s = read_line(p, (char *)s);
		else if (*s == '{')
			s = read_color(p, (char *)s, ft_strdup("\033[30m"));
		else
		{
			parse_string((char *)s, p, valist);
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


