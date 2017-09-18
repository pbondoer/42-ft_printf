/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 01:50:13 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/18 03:42:53 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Replaces conversion with string (one param)
*/

#define CONV 9

int			pf_transform(t_pf_param param, va_list list)
{
	static t_pf_handle	(handle[CONV]) = {
		{ .conversion = 's', .handle = pf_handle_string },
		{ .conversion = 'c', .handle = pf_handle_char },
		{ .conversion = '%', .handle = pf_handle_percent },
		{ .conversion = 'd', .handle = pf_handle_hex },
		{ .conversion = 'x', .handle = pf_handle_hex },
		{ .conversion = 'X', .handle = pf_handle_hex },
		{ .conversion = 'u', .handle = pf_handle_hex },
		{ .conversion = 'U', .handle = pf_handle_hex },
		{ .conversion = 'o', .handle = pf_handle_hex }
	};
	int i;

	i = 0;
	while (i < CONV)
	{
		if (param.conversion == handle[i].conversion)
		{
			return (handle[i].handle(param, list));
		}
		i++;
	}
	return (0);
}
