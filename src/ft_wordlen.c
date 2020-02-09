/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:57:06 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 18:57:29 by jbloodax         ###   ########.fr       */
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
