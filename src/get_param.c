/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 08:24:34 by pbondoer          #+#    #+#             */
/*   Updated: 2017/10/17 08:38:09 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "handlers.h"

int					handle_conversion(t_pf_param *p, const char *str, size_t *i)
{
	if (pf_is_conversion(str[*i]))
	{
		p->conversion = str[*i];
		(*i)++;
		return (0);
	}
	return (1);
}

static t_pf_param	big_conversions(t_pf_param param)
{
	if (param.conversion == 'D' || param.conversion == 'S' ||
			param.conversion == 'C' || param.conversion == 'O' ||
			param.conversion == 'U')
		param.modifier = L;
	if (param.conversion == 'D')
		param.conversion = 'd';
	if (param.conversion == 'S')
		param.conversion = 's';
	if (param.conversion == 'C')
		param.conversion = 'c';
	if (param.conversion == 'O')
		param.conversion = 'o';
	if (param.conversion == 'U')
		param.conversion = 'u';
	return (param);
}

t_pf_param			pf_get_param(const char *str, size_t len)
{
	static int		(*handle[6])(t_pf_param *, const char *, size_t *) = {
						handle_access, handle_flags, handle_width,
						handle_precision, handle_modifier, handle_conversion};
	t_pf_param		param;
	size_t			i;
	size_t			pos;

	i = 0;
	pos = 0;
	param = pf_param(str, len);
	while (i < 6)
	{
		if ((*handle[i])(&param, str + 1, &pos))
		{
			param.error = 1;
			break ;
		}
		i++;
	}
	if (param.conversion == 'i')
		param.conversion = 'd';
	if (param.conversion == 'p')
		param.modifier = LL;
	return (big_conversions(param));
}
