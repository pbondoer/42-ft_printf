/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 01:50:13 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/14 19:18:26 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_pf_string pf_handle_s(t_pf_param param, va_list list)
{
	t_pf_string	pf;

	(void)param;
	pf.str = va_arg(list, char *);
	pf.length = ft_strlen(pf.str);

	return (pf);
}

/*
** Replaces conversion with string (one param)
*/

t_pf_string pf_transform(t_pf_param param, va_list list)
{
	static t_pf_handle	(handle[2]) = {
		{ .conversion = 's', .handle = pf_handle_s },
		{ .conversion = '%', .handle = pf_handle_percent }
	};
	t_pf_string empty;
	int i;

	i = 0;
	while (i < 2)
	{
		if (param.conversion == handle[i].conversion)
		{
			return (handle[i].handle(param, list));
		}
		i++;
	}
	empty.str = NULL;
	empty.length = 0;
	return (empty);
}
