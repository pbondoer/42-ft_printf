/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 03:35:56 by pbondoer          #+#    #+#             */
/*   Updated: 2017/10/17 08:38:29 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					get_argument(const char *str, size_t len, int is_valid,
							va_list list)
{
	if (*str == '%' && is_valid)
		return (pf_transform(pf_get_param(str, len), list));
	else
		return (pf_write(str, len));
}

static int			parse_inner(const char *str, size_t *i, int *valid)
{
	if (!str[*i])
		return (1);
	while (str[*i] && pf_is_valid(str[*i]) && !pf_is_conversion(str[*i]))
		(*i)++;
	if ((*valid = str[*i] && pf_is_valid(str[*i])))
		(*i)++;
	else
		return (1);
	return (0);
}

/*
** Parse a format string and prints stuff
*/

int					pf_parse_format(const char *str, va_list list)
{
	size_t			i;
	size_t			start;
	int				valid;
	int				count;

	i = 0;
	count = 0;
	while (str[i])
	{
		start = i;
		valid = 0;
		if (str[i] == '%')
		{
			i++;
			if (parse_inner(str, &i, &valid))
				continue;
		}
		else
			while (str[i] && str[i] != '%')
				i++;
		count += get_argument(str + start, i - start, valid, list);
	}
	return (count);
}

/*
** Creates a printf param
** NOTE: All params are 0 at the start so no init is nescesary
*/

inline t_pf_param	pf_param(const char *str, size_t len)
{
	t_pf_param	param;

	param = (t_pf_param) {
		.str = (t_pf_string){ .str = str, .length = len },
			.access = 0,
			.flags = 0,
			.width = 0,
			.width_access = 0,
			.precision = 0,
			.modifier = NONE,
			.conversion = 0,
			.error = 0
	};
	return (param);
}

inline t_pf_string	pf_string(const char *str, size_t len)
{
	return ((t_pf_string) {
			.str = str,
			.length = len
			});
}
