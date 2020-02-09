/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float_determ.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:51:53 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:53:00 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_five_power(char *five_power, int power)
{
	char	*new;
	int		i;
	int		carry;
	int		len;

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

char	*get_two_power(char *two_power, int power)
{
	char	*new;
	int		i;
	int		carry;
	int		len;

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
	if (n > 0)
	{
		symbols = ft_charstr(n, c);
		if (is_after)
			s = ft_strjoin(tmp, symbols);
		else
			s = ft_strjoin(symbols, tmp);
		free(tmp);
		free(symbols);
	}
	return (s);
}
