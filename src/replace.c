/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 01:50:13 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/17 03:55:47 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Replaces conversion with string (one param)
*/

#define CONV 5

int			pf_transform(t_pf_param param, va_list list)
{
	static t_pf_handle	(handle[CONV]) = {
		{ .conversion = 's', .handle = pf_handle_string },
		{ .conversion = 'c', .handle = pf_handle_char },
		{ .conversion = '%', .handle = pf_handle_percent },
		{ .conversion = 'x', .handle = pf_handle_hex },
		{ .conversion = 'X', .handle = pf_handle_hex }
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
