/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 04:44:30 by akraig            #+#    #+#             */
/*   Updated: 2019/12/21 17:46:50 by akraig           ###   ########.fr       */
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
