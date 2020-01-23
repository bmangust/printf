/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 08:50:43 by akraig            #+#    #+#             */
/*   Updated: 2020/01/22 16:11:23 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	len;
	char	*mapped;

	i = 0;
	if (s && f)
	{
		len = ft_strlen(s);
		mapped = (char*)malloc((len + 1) * sizeof(char));
		if (mapped)
		{
			while (i < len)
			{
				mapped[i] = f(s[i]);
				i++;
			}
			mapped[i] = '\0';
			return (mapped);
		}
	}
	return (NULL);
}
