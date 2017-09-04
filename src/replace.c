/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 01:50:13 by pbondoer          #+#    #+#             */
/*   Updated: 2017/02/09 02:00:46 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_pf_string *pf_handle_s(param) {
	return (param->str);
}

/*
** Replaces conversion with string (one param)
*/

static void pf_transform(t_pf_param *param)
{
	static t_pf_handle	*(handle[1]) = {
		// handlers
	};

	while (i < 1)
	{
		if (param->conversion == handle[i]->conversion)
		{
			handle[i]->handle(param);
		}
		i++;
	}
}
