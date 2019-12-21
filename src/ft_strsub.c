/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 08:20:04 by akraig            #+#    #+#             */
/*   Updated: 2019/12/21 20:55:28 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s || !(sub = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	sub = ft_strncpy(sub, (char*)s + start, len);
	sub[len] = '\0';
	return (sub);
}
