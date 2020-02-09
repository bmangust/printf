/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:13:35 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:13:41 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	tmp = NULL;
	if (*alst && del)
	{
		while ((*alst)->next)
		{
			tmp = (*alst);
			(*alst) = (*alst)->next;
			ft_lstdelone(&tmp, del);
		}
		ft_lstdelone(alst, del);
	}
}
