/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:07:39 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 19:07:56 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *append, size_t n)
{
	size_t i;
	size_t len;
	size_t applen;

	i = 0;
	applen = ft_strlen(append);
	len = ft_strlen(dest);
	while (i < applen && i < n)
	{
		dest[len + i] = append[i];
		i++;
	}
	dest[len + i] = '\0';
	return (dest);
}
