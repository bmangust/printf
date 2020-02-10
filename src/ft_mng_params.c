/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mng_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:33:10 by akraig            #+#    #+#             */
/*   Updated: 2020/02/10 21:51:08 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	p->size = 0;
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
}

int			del_param(t_parse *p, va_list valist)
{
	int printed;

	if (!p)
		return (-1);
	printed = p->printed;
	if (p->flags)
		free(p->flags);
	if (p->buf)
		free(p->buf);
	free(p);
	va_end(valist);
	return (printed);
}
