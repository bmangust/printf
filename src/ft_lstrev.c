/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 02:25:52 by akraig            #+#    #+#             */
/*   Updated: 2019/12/21 17:46:50 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **head)
{
	t_list *p0;
	t_list *p1;
	t_list *p2;

	p0 = NULL;
	p1 = *head;
	p2 = p1->next;
	while (p2)
	{
		p1->next = p0;
		p0 = p1;
		p1 = p2;
		p2 = p2->next;
	}
	p1->next = p0;
	*head = p1;
}
