/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:02:19 by jbloodax          #+#    #+#             */
/*   Updated: 2020/02/09 19:02:38 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s && start >= s_len)
		return (ft_strnew(0));
	if (!s || !(sub = ft_strnew(len)))
		return (NULL);
	sub = ft_strncpy(sub, (char*)s + start, len);
	sub[len] = '\0';
	return (sub);
}
