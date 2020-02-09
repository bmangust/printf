/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:09:08 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 19:09:19 by jbloodax         ###   ########.fr       */
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
