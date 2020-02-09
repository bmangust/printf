/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:34:13 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 19:34:29 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int64_t n)
{
	ft_putnbr_fd(n, 1);
}

void	ft_unsigned_putnbr(uint64_t n)
{
	ft_unsigned_putnbr_fd(n, 1);
}
