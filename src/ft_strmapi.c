/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:08:26 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 19:08:46 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*mapped;

	i = 0;
	if (s && f)
	{
		len = ft_strlen(s);
		mapped = (char*)malloc((len + 1) * sizeof(char));
		if (mapped)
		{
			while (i < len)
			{
				mapped[i] = f(i, s[i]);
				i++;
			}
			mapped[i] = '\0';
			return (mapped);
		}
	}
	return (NULL);
}
