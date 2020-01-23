/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:22:17 by akraig            #+#    #+#             */
/*   Updated: 2020/01/23 12:27:16 by akraig           ###   ########.fr       */
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
