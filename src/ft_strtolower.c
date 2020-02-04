/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:19:47 by akraig            #+#    #+#             */
/*   Updated: 2020/02/04 18:19:58 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *str, int is_freeable)
{
	int		i;
	int		len;
	char	*new;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (!(new = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (++i < len)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			new[i] = str[i] + 32;
		else
			new[i] = str[i];
	}
	if (is_freeable)
		free(str);
	return (new);
}
