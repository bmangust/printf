/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:23:04 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 19:23:24 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		dest = (char*)malloc((len + 1) * sizeof(char));
		if (dest)
		{
			while (i < len)
			{
				dest[i] = s[i];
				i++;
			}
			dest[i] = '\0';
			return (dest);
		}
	}
	return (NULL);
}
