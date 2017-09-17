/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 18:53:18 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/17 03:28:14 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_handle_percent(t_pf_param param, va_list list)
{
	(void)list;
	int count;

	count = 0;
	if ((param.flags & PF_FLAG_MINUS) == 0 && param.width > 1)
		count += pf_repeat(' ', param.width - 1);
	count += pf_write("%", 1);
	if ((param.flags & PF_FLAG_MINUS) != 0 && param.width > 1)
		count += pf_repeat(' ', param.width - 1);
	return (count);
}
