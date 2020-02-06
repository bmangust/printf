/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mng_params.c	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/01/31 16:14:34 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_node		*new_piece(char type, int mod)
{
	t_node	*new;

	if (!(new = (t_node*)malloc(sizeof(t_node))))
		return (NULL);
	new->mod = mod;
	new->type = type;
	new->s = NULL;
	new->c = 0;
	new->n = 0;
	new->f = 0;
	new->next = new;
	new->prev = new;
	return (new);
}

t_parse		*new_param(void)
{
	t_parse	*new;

	if (!(new = (t_parse*)malloc(sizeof(t_parse))))
		return (NULL);
	new->type = 0;
	new->size = 0;
	new->is_signed = 0;
	new->spaces = 0;
	new->flags = NULL;
	new->width = 0;
	new->prec = 0;
	new->zero_prec = 0;
	new->printed = 0;
	new->length = 0;
	new->skip_0_flag = 0;
	new->E = 0;
	new->next = NULL;
	new->buf = NULL;
	new->arg_i = 0;
	new->arg_d = 0;
	new->arg_s = NULL;
	return (new);
}

void		clear_param(t_parse *p)
{
	if (!p)
		return ;
//	p->type = 0;
	p->size = 0;
//	p->is_signed = 0;
	p->spaces = 0;
	p->flags ? free(p->flags) : 0;
	p->flags = NULL;
	p->width = 0;
	p->prec = 0;
	p->zero_prec = 0;
	p->length = 0;
	p->skip_0_flag = 0;
	p->E = 0;
	p->next = NULL;
//	p->arg_i = 0;
//	p->arg_d = 0;
//	p->arg_s = NULL;
}

void		del_param(t_parse *p, va_list valist)
{
	if (!p)
		return ;
	if (p->flags)
		free(p->flags);
	if (p->buf)
		free(p->buf);
	free(p);
	va_end(valist);
}

t_node		*add_last_piece(t_node **head, t_node *new)
{
	t_node *tmp;

	if (head && new)
	{
		if (*head)
		{
			tmp = (*head)->prev;
			new->next = tmp->next;
			new->next->prev = new;
			new->prev = tmp;
			tmp->next = new;
		}
		else
			*head = new;
		return (new);
	}
	return (NULL);
}
