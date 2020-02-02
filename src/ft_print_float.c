/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/01/25 18:06:01 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_double *get_bits(double d, float f, t_double *num)
{
	int64_t	dl;
	int		di;
	char	*bits;
	char	*tmp;
	int		i;

	dl = *((long long*)&d);
	di = *((int*)&f);
	i = -1;
	bits = ft_strnew(64);
	if (num->is_double)
		while (++i < 64)
			bits[i] = ((dl >> (63 - i)) & 1) + '0';
	else
		while (++i < 32)
			bits[i] = ((di >> (31 - i)) & 1) + '0';
	num->sign[0] = bits[0];
	num->exp = ft_strsub(bits, 1, (num->is_double) ? 11 : 8);
	tmp = (num->is_double) ? ft_strsub(bits, 12, 52)
						   : ft_strsub(bits, 9, 23);
	num->mant = ft_strjoin("1", tmp);
	free(tmp);
	return (num);
}

t_double *new_double(double d, float f, int is_double)
{
	t_double *num = (t_double*)malloc(sizeof(t_double));

	num->is_double = is_double;
	num->sign = ft_strnew(1);
	num->exp = NULL;
	num->mant = NULL;
	num = is_double ? get_bits(d, 0, num) : get_bits(0, f, num);
	return (num);
}

void	free_double(t_double *num)
{
	free(num->sign);
	free(num->exp);
	free(num->mant);
	free(num);
}

int64_t		bin_to_dec(char *bin)
{
	int i;
	int len;
	int dec;

	len = ft_strlen(bin);
	i = len--;
	dec = 0;
	while (--i >= 0)
		if (bin[i] == '1')
			dec += ft_pow(2, len - i);
	return (dec);
}
int		find_last_digit(char *mant)
{
	int i;

	i = (int)ft_strlen(mant) - 1;
	while (i >= 0 && mant[i] != '1')
		i--;
	return (i);
}

char 	*get_five_power(char *five_power, int power)
{
	char	*new;
	int		i;
	int 	carry;
	int 	len;

	i = -1;
	len = five_power ? ft_strlen(five_power) : 1;
	if (power == 1)
		return (ft_strdup("5"));
	new = ft_charstr(len + 1, '0');
	carry = 0;
	while (++i < len + 1)
		if (five_power[i])
		{
			new[i] = (five_power[i] - '0' + carry) / 2 + '0';
			carry = (five_power[i] - '0') % 2 * 10;
		}
		else if (!five_power[i])
			new[i] = '5';
	free(five_power);
	return (new);
}

char 	*get_two_power(char *two_power, int power)
{
	char	*new;
	int		i;
	int 	carry;
	int 	len;

	i = -1;
	len = two_power ? ft_strlen(two_power) : 1;
	if (power == 0)
		return (ft_strdup("1"));
	new = ft_charstr((power - 1) / 3 + 1, '0');
	carry = 0;
	while (++i < len + 1)
		if (two_power[i])
		{
			new[i] = ((two_power[i] - '0') * 2 + carry) % 10 + '0';
			carry = (two_power[i] - '0') * 2 / 10;
		}
		else if (!two_power[i] && carry)
			new[i] = carry + '0';
	free(two_power);
	return (new);
}

void	sum(char *summ, char *add)
{
	int i;
	int carry;
	int sum;

	i = ft_strlen(add);
	carry = 0;
	while (--i >= 0)
	{
		if (add[i] == '0' && carry == 0)
			continue ;
		sum = summ[i] + add[i] + carry - 96;
		carry = (sum > 9) ? 1 : 0;
		summ[i] = sum % 10 + '0';
	}
}

char	*add_symbols(char *s, char c, size_t n, int is_after)
{
	char	*tmp;
	char	*symbols;

	tmp = s;
	symbols = ft_charstr(n, c);
	if (is_after)
		s = ft_strjoin(tmp, symbols);
	else
		s = ft_strjoin(symbols, tmp);
	free(tmp);
	free(symbols);
	return (s);
}

char	*round_fractional(char *fract, t_parse *p)
{
	int 	i;

	if (p->prec > (int)ft_strlen(fract))
		return (add_symbols(fract, '0', p->prec - ft_strlen(fract), 1));
	i = p->prec;
	if (fract[i] >= '5' && p->prec > 0)
	{
		p->E = (fract[i - 1] - '0' + 1) / 10;
		if (!p->E)
			fract[p->prec - 1] = (fract[p->prec - 1] - '0' + 1) % 10 + '0';
		while (p->E == 1 && --i >= 0 && fract[i] == '9')
		{
			fract[i - 1] = (fract[i - 1] - '0' + p->E) % 10 + '0';
			fract[i] = '0';
			p->E = (fract[i - 1] - '0' + 1) / 10;
		}
	}
	fract[p->prec] = '\0';
	return (fract);
}

/*
**	is_integer may be 1 for integer or -1 for fractional
*/

char	*count_exp(t_double num, int is_integer)
{
	int		exp;
	int		diff;
	char	*bin;

	exp = bin_to_dec(num.exp);
	diff = (num.is_double) ? 1023 : 127;
	exp -= diff;
	if (exp >= 0 && exp < 53)
		bin = (is_integer == 1) ? ft_strsub(num.mant, 0, exp + 1)
								: ft_strsub(num.mant, exp + 1, 64);
	else if (exp > 52)
		bin = add_symbols(bin, '0', exp - 52, 1);
	else
		bin = add_symbols(bin, '0', -exp - 1, 0);
	return (bin);
}

char	*get_fractional(t_double num, t_parse *p)
{
	char	*fract;
	char	*five_power;
	char	*fract_bin;
	int 	i;
	int 	fract_len;

	i = -1;
	fract_bin = count_exp(num, -1);
	fract_len = find_last_digit(fract_bin) + 1;
	fract = ft_charstr(fract_len, '0');
	five_power = NULL;
	while (i++ < fract_len)
	{
		five_power = get_five_power(five_power, i + 1);
		if (fract_bin[i] == '1')
			sum(fract, five_power);
	}
	fract = round_fractional(fract, p);
	free (fract_bin);
	free (five_power);
	return (fract);
}

char	*get_integer(t_double num, t_parse *p)
{
	char	*intg;
	char	*two_power;
	char	*integer_bin;
	int 	i;
	int 	integer_len;

	i = -1;
	integer_bin = ft_strrev(count_exp(num, 1));
	integer_len = find_last_digit(integer_bin) + 1;
	intg = ft_charstr(find_last_digit(integer_bin) + 1, '0');
	two_power = NULL;
	while (i++ < integer_len)
	{
		two_power = get_two_power(two_power, i);
		if (integer_bin[i] == '1')
			sum(intg, two_power);
	}
	intg = ft_strrev(intg);
	free (integer_bin);
	free (two_power);
	if (ft_strchr(p->flags, '+') || num.sign[0] != '0')
	{
		two_power = intg;
		intg = num.sign ? ft_strjoin("-", intg) : ft_strjoin("+", intg);
		free(two_power);
	}
	return (intg);

}

//static long long int	float_base(double x)
//{
//	double			rest;
//	int				e;
//	long long int	base;
//
//	e = -FLOAT_POWER;
//	base = 0;
//	while (e++ < FLOAT_POWER)
//	{
//		rest = x / ft_pow(2, e);
//		if (rest >= 1 && rest < 2)
//		{
//			e += 1;
//			break ;
//		}
//	}
//	rest = x;
//	while (rest > 0 && e-- > 0)
//	{
//		base += ft_pow(2, e);
//		rest = x - base;
//	}
//	base += rest;
//	return (base);
//}

//static void		lld_to_str(long long int integer, long long int	fract, t_parse *p)
//{
//	char	*str_int;
//	char	*str_fract;
//	char	*str;
//	int		sign;
//
//	sign = 0;
//	(ft_strchr(p->flags, '+')) ? sign = 1 : sign;
//	str_int = ft_ltoa(integer, (sign + 1));
//	sign = 0;
//	if (fract == 0 && p->prec != 0)
//	{
//		str_fract = ft_strnew((size_t) p->prec);
//		while (p->prec-- > 0)
//			str_fract[sign++] = '0';
//	}
//	else
//		str_fract = ft_ltoa(fract, sign);
//	str = ft_strjoin(str_int, str_fract);
//	p->prec = 0;
//	print_str(str, p);
//	free(str_int);
//	free(str_fract);
//	free(str);
//}

//int 	is_special_double(t_double num)
//{
//
//}

char	*concat_parts(char *integer, char *fract, t_parse *p)
{
	char *tmp;

	tmp = integer;
	if (!p->zero_prec)
	{
		p->prec += ((int)ft_strlen(integer) + 1);
		integer = ft_strjoin(integer, ".");
		free(tmp);
		tmp = integer;
		integer = ft_strjoin(integer, fract);
		free(tmp);
	}
	return (integer);
}

void	print_float(double d, t_parse *p)
{
	char		*integer;
	char		*fract;
	t_double	*num;

	if (!p->prec)
		p->prec = 6;
	num = new_double(d, 0, 1);
	integer = get_integer(*num, p);
	fract = (p->zero_prec) ? NULL : get_fractional(*num, p);
	integer = concat_parts(integer, fract, p);
	print_str(integer, p);
	free_double(num);
}

