/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 08:21:00 by pbondoer          #+#    #+#             */
/*   Updated: 2018/01/24 18:08:09 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "handlers.h"
#include "helpers.h"

int			handle_access(t_pf_param *param, const char *str, size_t *i)
{
	int access;
	int t;

	t = *i;
	if (!pf_isdigit(str[*i]))
		return (0);
	if (pf_atoi(str, 0, &access, i) || str[*i] != '$')
	{
		*i = t;
		return (0);
	}
	(*i)++;
	param->access = access;
	return (0);
}

int			handle_flags(t_pf_param *param, const char *str, size_t *i)
{
	char c;

	while (*i < param->str.length)
	{
		c = str[*i];
		if (pf_is_flag(c))
		{
			if (c == '#')
				param->flags |= PF_FLAG_HASH;
			else if (c == '0')
				param->flags |= PF_FLAG_ZERO;
			else if (c == '-')
				param->flags |= PF_FLAG_MINUS;
			else if (c == '+')
				param->flags |= PF_FLAG_PLUS;
			else if (c == ' ')
				param->flags |= PF_FLAG_SPACE;
			else if (c == '\'')
				param->flags |= PF_FLAG_APOSTROPHE;
		}
		else
			return (0);
		(*i)++;
	}
	return (1);
}

int			handle_width(t_pf_param *param, const char *str, size_t *i)
{
	int width;
	int is_pos;

	if ((is_pos = (str[*i] == '*')))
		(*i)++;
	if (pf_atoi(str, 0, &width, i) && !is_pos)
		return (1);
	if (is_pos)
	{
		if (str[*i] == '$')
			(*i)++;
		else
			return (1);
		param->width_access = width;
	}
	else
		param->width = width;
	return (0);
}

int			handle_precision(t_pf_param *p, const char *str, size_t *i)
{
	int precision;

	p->precision = -1;
	if (str[*i] != '.')
		return (0);
	p->precision = 0;
	(*i)++;
	if (pf_atoi(str, 0, &precision, i))
		return (1);
	p->precision = precision;
	return (0);
}

int			handle_modifier(t_pf_param *p, const char *str, size_t *i)
{
	t_pf_modifier	m;

	m = NONE;
	if (!pf_is_modifier(str[*i]))
		return (0);
	if (str[*i] == 'l')
	{
		if (str[*i + 1] == 'l' && ++(*i))
			m = LL;
		else
			m = L;
	}
	else if (str[*i] == 'h')
	{
		if (str[*i + 1] == 'h' && ++(*i))
			m = HH;
		else
			m = H;
	}
	else if (str[*i] == 'j')
		m = J;
	else if (str[*i] == 'z')
		m = Z;
	p->modifier = m;
	return ((*i)++ & 0);
}
