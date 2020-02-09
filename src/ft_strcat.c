/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:27:09 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 19:27:25 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *append)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(dest);
	while (append[i])
	{
		dest[len + i] = append[i];
		i++;
	}
	dest[len + i] = '\0';
	return (dest);
}
