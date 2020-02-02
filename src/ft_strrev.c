/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 02:03:48 by akraig            #+#    #+#             */
/*   Updated: 2020/01/23 12:27:16 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*rev;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	j = ft_strlen(str);
	rev = ft_strnew(j);
	while (--j >= 0)
		rev[i++] = str[j];
	free(str);
	return (rev);
}
