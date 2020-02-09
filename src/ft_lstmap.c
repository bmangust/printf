/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:15:42 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:15:48 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *head;
	t_list *tmp;

	tmp = lst;
	head = NULL;
	if (lst != NULL && f != NULL)
	{
		while (tmp)
		{
			ft_lstadd_last(&head, f(tmp));
			tmp = tmp->next;
		}
		return (head);
	}
	return (NULL);
}
