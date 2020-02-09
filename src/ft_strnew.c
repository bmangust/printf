/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:04:35 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 19:04:50 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*s;

	i = 0;
	if ((size + 1) == 0)
		return (0);
	s = (char*)malloc((size + 1) * sizeof(char));
	if (s)
	{
		while (i <= size)
		{
			s[i] = '\0';
			i++;
		}
		return (s);
	}
	return (NULL);
}
