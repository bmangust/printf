/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2019/12/05 21:24:30 by akraig           ###   ########.fr       */
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

t_parse		*new_param()
{
	t_parse	*new;

	if (!(new = (t_parse*)malloc(sizeof(t_parse))))
		return (NULL);
	new->type = NULL;
	new->length = 0;
    new->flag = 0;
    new->width = 0;
    new->precision = 0;
    new->align = 0;
	new->next = NULL;
	return (new);
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

int			int_length(int n)
{
	int length;

	length = 0;
	while (n)
	{
		n /= 10;
		++length;
	}
	return (length);
}

void	write_type(char *type, char length, char tmp)
{
	type = ft_strnew(22);
	if (tmp == 'd' || tmp == 'i')
		if (length == 0)
			ft_strcpy(type, "int");
	else if (tmp == 'c')
		ft_strcpy(type, "char");
	else if (tmp == 's')
		ft_strcpy(type, "char *");
}

t_parse	*parse_string(char *tmp, t_parse *params)
{
	char	*types;
	char	*lengths;
	char	*flags;
	int		stop;

	stop = 0;
	types = "%diufFeEgGxXoscpaAn";
	lengths = "hlhhllLzjt";
	flags = "-+ 0#";
	while (!stop && *tmp)
	{
		if (ft_strchr(flags, *tmp))
			params->flag = *tmp;
		else if ((params->width = ft_atoi(tmp)))
			tmp += int_length(params->width) - 1;	//not sure, check
		else if (ft_strchr(lengths, *tmp))
		{
			params->length = ft_strnew(2);
			if (ft_strchr(flags, *(tmp + 1)))
			{
				ft_strncpy(params->length, tmp, 2);
				++tmp;
			}
			else
				params->length[0] = *tmp;
		}
		else if (ft_strchr(types, *tmp))
		{
			write_type(params->type, params->length,*tmp);
			stop = 1;
		}
		++tmp;
	}
	return (params);
}

int		ft_printf(const char * restrict s, ... )
{
	va_list	valist;
	t_parse	*params;
	char	*tmp;

	params = new_param();
	tmp = (char*)s;
	va_start(valist, s);
	while (*tmp)
	{
		if (*tmp != '%')
			ft_putchar(*tmp);
		else
		{
			tmp++;
			parse_string(tmp, params);
			print_arg();
			//free params->width, params->type and params

			/*
			if (*tmp == 'c')
				ft_putchar(va_arg(valist, int));
			else if (*tmp == 'd')
				ft_putnbr(va_arg(valist, int));
			else if (*tmp == 's')
				ft_putstr(va_arg(valist, char*));
				*/
		}
		tmp++;
	}
	return (0);
}
