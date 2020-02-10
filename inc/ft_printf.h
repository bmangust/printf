/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:07:11 by akraig            #+#    #+#             */
/*   Updated: 2020/02/10 22:04:40 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include "libft.h"

# define MAX(a,b) ((a > b) ? a : b)

#define INT 0
#define SHORT (1 << 0)
#define LONG (1 << 1)
#define LONGLONG (1 << 2)
#define CHAR (1 << 4)

typedef struct		s_parse
{
	char 			type;
	unsigned int	size;
	int				is_signed;
	int				spaces;
	char			*flags;
	int				width;
	int				prec;
	int				zero_prec;
	int 			skip_0_flag;
	int				E;
	int				printed;
	int				length;
	char			*next;
	char			*buf;
	int64_t 		arg_i;
	double			arg_d;
	char			*arg_s;
}					t_parse;

typedef struct      s_double
{
	char *special;
	char *sign;
	char *exp;
	char *mant;
}                   t_double;

int					ft_printf(const char *restrict s, ...);
t_parse				*parse_string(char *s, t_parse *params, va_list valist);
void				buffer(t_parse *p, char *s, int freeable);
void				print_char(char c, t_parse *p);
char				*print_float(double d, t_parse *p);
void				print_str(char *str, t_parse *p);
t_double			*new_double(double d);
int64_t				bin_to_dec(char *bin);
char				*get_fractional(t_double *num, t_parse *p);
char				*add_symbols(char *s, char c, size_t n, int is_after);
char				*read_color(t_parse *p, char *s, char *code);
char			    *read_width(t_parse *p, char *tmp, va_list valist);
char				*read_size(t_parse *p, char *tmp);
char				*read_flags(char *tmp, t_parse *p);
char				*read_prec(char *tmp, t_parse *p, va_list valist);
void				read_type(char *tmp, t_parse *p);
t_parse				*new_param(void);
void				clear_param(t_parse *p);
int					del_param(t_parse *p, va_list valist);
int					int_length_and_update(int64_t n, t_parse *p);
int 	    		is_positive(int64_t n, t_parse *p);
void				add_sign(int64_t n, t_parse *p, char **num);
char   				*fill_width(t_parse *p, char *num, char sign);
char				*get_int(t_parse *p, int64_t n);
void				print_s_int(int64_t n, t_parse *p);
void				print_int(int64_t n, t_parse *p);
char 				*print_base_u(uint64_t v, t_parse *p, int base);
char				*print_base(int64_t v, t_parse *p, int base);
void				print_percentage(t_parse *p);
void				print_arg(t_parse *p);
void			    get_and_print_arg(va_list valist, t_parse *p);
t_parse				*parse_string(char *tmp, t_parse *p, va_list valist);
void				buffer(t_parse *p, char *s, int freeable);
char				*read_line(t_parse *p, char *s);
char				*is_special_double(t_double num, char *mant);
char 				*float_e(char *intg, int prec, t_parse *p, int e);
char 				*float_g(char *intg, char *fract, t_parse *p, int n);
t_double 			*get_bits(double d, t_double *num);
t_double			 *new_double(double d);
void				free_double(t_double *num);
int64_t				bin_to_dec(char *bin);
int					find_last_digit(char *mant);
char 				*get_five_power(char *five_power, int power);
char 				*get_two_power(char *two_power, int power);
void				sum(char *summ, char *add);
void				sum2(char *summ, char *add);
char				*add_symbols(char *s, char c, size_t n, int is_after);
char				*round_fractional(char *fract, int prec, int is_int, t_parse *p);
char				*count_exp(t_double *num, int is_integer);
char				*get_fractional(t_double *num, t_parse *p);
char				*get_integer(t_double *num, t_parse *p);
char				*concat_parts(char *integer, char *fract, t_parse *p);

#endif
