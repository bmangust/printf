/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 12:14:41 by akraig            #+#    #+#             */
/*   Updated: 2019/12/21 17:46:51 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wordlen(const char *s, char c, int start)
{
	int cnt;

	cnt = 0;
	while (s[start] != '\0' && s[start] != c)
	{
		cnt++;
		start++;
	}
	return (cnt);
}
