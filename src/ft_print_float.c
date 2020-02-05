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

char	*is_special_double(t_double num, char *mant)
{
	char *s;

	s = NULL;
	if (num.is_double)
	{
		if (!ft_strcmp(num.exp, "11111111111") && !ft_strchr(mant, '1'))
			s = num.sign[0] == '0' ? ft_strdup("inf") : ft_strdup("-inf");
		else if (!ft_strcmp(num.exp, "11111111111"))
			s = ft_strdup("nan");
	}
	else
	{
		if (!ft_strcmp(num.exp, "11111111") && !ft_strchr(mant, '1'))
			s = num.sign[0] == '0' ? ft_strdup("inf") : ft_strdup("-inf");
		else if (!ft_strcmp(num.exp, "11111111"))
			s = ft_strdup("nan");
	}
	return (s);
}

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
	num->special = is_special_double(*num, tmp);
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
	free(num->special);
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

void	sum2(char *summ, char *add)
{
	int i;
	int len;
	int carry;
	int sum;

	len = ft_strlen(add);
	i = -1;
	carry = 0;
	while (++i < len)
	{
		if (add[i] == '0' && carry == 0)
			continue ;
		sum = summ[i] + add[i] + carry - 96;
		carry = (sum > 9) ? 1 : 0;
		summ[i] = sum % 10 + '0';
	}
	if (carry)
		summ[i] = '1';
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

char	*round_fractional(char *fract, int prec, int is_int, t_parse *p)
{
	int 	i;

	if (prec > (int)ft_strlen(fract))
		return (add_symbols(fract, '0', prec - ft_strlen(fract), 1));
	i = prec;
	if ((fract[i] >= '5' || is_int) && prec > 0)
	{
		p->E = (fract[i - 1] - '0' + p->E) / 10;
		if (!p->E)
			fract[prec - 1] = (fract[prec - 1] - '0' + 1) % 10 + '0';
		while (p->E == 1 && --i >= 0)
		{
			p->E = (fract[i] - '0' + 1) / 10;
			fract[i] = (fract[i] - '0' + 1) % 10 + '0';
		}
	}
	if (is_int && p->E)
		fract = add_symbols(fract, '1', 1, 0);
	if (!is_int)
		fract[prec] = '\0';
	return (fract);
}

//"999999 9989999963645459502004086971282958984375"
//      ^
/*
**	is_integer may be 1 for integer or -1 for fractional
*/

char	*count_exp(t_double *num, int is_integer)
{
	int		exp;
	int		diff;
	char	*bin;

	exp = bin_to_dec(num->exp);
	diff = (num->is_double) ? 1023 : 127;
	exp -= diff;
	if (exp >= 0 && exp < 53)
		return ((is_integer) ? ft_strsub(num->mant, 0, exp + 1)
								  : ft_strsub(num->mant, exp + 1, 53));
	if (exp > 52 && is_integer)
	{
		bin = add_symbols(num->mant, '0', exp - 52, 1);
		num->mant = ft_strdup("0");
	}
	else if (is_integer)
		bin = ft_strdup("0");
	else if (exp < 0)
	{
		bin = add_symbols(num->mant, '0', -exp - 1, 0);
		num->mant = NULL;
	}
	else
		bin = ft_strdup(num->mant);
	return (bin);
}

char	*get_fractional(t_double *num, t_parse *p)
{
	char	*fract;
	char	*five_power;
	char	*fract_bin;
	int 	i;
	int 	fract_len;

	i = -1;
	fract_bin = count_exp(num, 0);
	fract_len = find_last_digit(fract_bin) + 1;
	fract = ft_charstr(fract_len, '0');
	five_power = NULL;
	while (i++ < fract_len)
	{
		five_power = get_five_power(five_power, i + 1);
		if (fract_bin[i] == '1')
			sum(fract, five_power);
	}
	fract = round_fractional(fract, p->prec, 0, p);
	free (fract_bin);
	free (five_power);
	return (fract);
}

char	*get_integer(t_double *num, t_parse *p)
{
	char	*intg;
	char	*two_power;
	char	*integer_bin;
	int 	i;
	int 	integer_len;

	i = -1;
	integer_bin = ft_strrev(count_exp(num, 1));
	p->E = find_last_digit(integer_bin);
	integer_len = p->E ? p->E / 3 + 1 : 1;
	intg = ft_charstr(integer_len, '0');
	two_power = NULL;
	while (++i <= p->E)
	{
		two_power = get_two_power(two_power, i);
		if (integer_bin[i] == '1')
			sum2(intg, two_power);
	}
	while (integer_len > 1 && intg[ft_strlen(intg) - 1] == '0')
		intg[ft_strlen(intg) - 1] = '\0';
	free (integer_bin);
	free (two_power);
	return (intg);
}

char	*concat_parts(char *integer, char *fract, t_parse *p)
{
	char *tmp;

	if (p->E)
		integer = round_fractional(integer, ft_strlen(integer), 1, p);
	tmp = integer;
	if (!p->zero_prec || ft_strchr("eEgG", p->type))
	{
		integer = ft_strjoin(integer, ".");
		free(tmp);
		tmp = integer;
		integer = ft_strjoin(integer, fract);
		free(tmp);
	}
	return (integer);
}

char	*print_float_internal(double d, t_parse *p)
{
	char		*integer;
	char		*fract;
	t_double	*num;

	num = new_double(d, 0, 1);
	if (num->special && (p->type == 'F' || p->type == 'G' || p->type == 'E'))
		integer = ft_strtoupper(num->special, 1);
	else if (num->special)
		integer = ft_strdup(num->special);
	if (num->special == NULL)
	{
		if (!p->zero_prec && !p->prec)
			p->prec = 6;
		integer = ft_strrev(get_integer(num, p));
		p->E = 1;
		fract = (p->zero_prec) ? NULL : get_fractional(num, p);
		integer = concat_parts(integer, fract, p);
		num->sign[0] == '1' ? integer = add_symbols(integer, '-', 1, 0) : 0;
		(num->sign[0] == '0' && ft_strchr(p->flags, '+')) ?
				integer = add_symbols(integer, '+', 1, 0) : 0;
		(num->sign[0] == '0' && ft_strchr(p->flags, ' ')) ?
				integer = add_symbols(integer, ' ', 1, 0) : 0;
	}
	free_double(num);
	return (integer);
}

char	*print_float(double d, t_parse *p)
{
	if (p->size == LONGLONG || p->size == LONG)
		return (print_float_internal((double)d, p));
	else
		return (print_float_internal((float)d, p));
}

