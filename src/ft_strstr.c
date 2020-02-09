/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:14:25 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 19:14:48 by jbloodax         ###   ########.fr       */
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
