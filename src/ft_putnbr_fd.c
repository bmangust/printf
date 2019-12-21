/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 01:22:26 by akraig            #+#    #+#             */
/*   Updated: 2019/12/21 17:46:57 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_cycles(intmax_t nb, int lower_f, int fd)
{
	int temp[10];
	int i;

	i = 0;
	while (nb > 9)
	{
		temp[i] = nb % 10;
		nb = nb / 10;
		i++;
	}
	temp[i] = nb;
	if (lower_f)
		temp[0] = 8;
	while (i >= 0)
	{
		ft_putchar_fd(temp[i] + '0', fd);
		i--;
	}
}

void		ft_putnbr_fd(intmax_t nb, int fd)
{
	int lower_f;

	lower_f = 0;
//	if (nb == -2147483648)
//	{
//		lower_f = 1;
//		nb++;
//	}
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar_fd('-', fd);
	}
	ft_cycles(nb, lower_f, fd);
}
