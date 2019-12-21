/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 06:08:46 by akraig            #+#    #+#             */
/*   Updated: 2019/12/21 17:46:50 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strstr(const char *src, const char *aim)
{
	size_t	srclen;
	size_t	aimlen;

	srclen = ft_strlen(src);
	aimlen = ft_strlen(aim);
	if (aimlen == 0)
		return ((char *)src);
	return (ft_strnstr(src, aim, srclen));
}
