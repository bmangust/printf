/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:57:13 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:01:08 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*read_other(t_parse *p, char *s, int found)
{
	if ((found = ft_strncmp("{DEFAULT}", s, 9)) == 0)
		buffer(p, "\033[0m", 0);
	else if ((found = ft_strncmp("{BOLDFACE}", s, 10)) == 0)
		buffer(p, "\033[1m", 0);
	else if ((found = ft_strncmp("{SEMIBRIGHT}", s, 12)) == 0)
		buffer(p, "\033[2m", 0);
	else if ((found = ft_strncmp("{ITALIC}", s, 8)) == 0)
		buffer(p, "\033[3m", 0);
	else if ((found = ft_strncmp("{INDERLINE}", s, 11)) == 0)
		buffer(p, "\033[4m", 0);
	else if ((found = ft_strncmp("{BLINK}", s, 7)) == 0)
		buffer(p, "\033[5m", 0);
	else
		buffer(p, "{", 0);
	if (found == 0)
		s = ft_strchr(s, '}');
	return (s);
}

static char	**split_color(void)
{
	char	**ar;
	char	*ident;

	ident = "{BLACK,{RED,{GREEN,{YELLOW,{BLUE,{MAGENTA,{CYAN,{GREY";
	ar = ft_strsplit(ident, ',');
	return (ar);
}

char		*read_color(t_parse *p, char *s, char *code)
{
	int		found;
	char	**ar;
	int		i;

	ar = split_color();
	found = 42;
	i = -1;
	while (ar[++i] && found)
		found = ft_strncmp(ar[i], s, ft_strlen(ar[i]));
	if (!found && --i)
	{
		if (*(s + (ft_strlen(ar[i]))) == '}')
			code[3] = i + '0';
		else if ((found = ft_strncmp("_BG}", (s + (ft_strlen(ar[i]))), 4)) == 0)
		{
			code[2] = 4 + '0';
			code[3] = i + '0';
		}
		buffer(p, code, 1);
		s = ft_strchr(s, '}');
	}
	else if (found != 0)
		s = read_other(p, s, found);
	return (s);
}
