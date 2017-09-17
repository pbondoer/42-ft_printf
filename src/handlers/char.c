/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 03:28:28 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/17 03:32:53 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_handle_char(t_pf_param param, va_list list)
{
	int count;
	int c;

	count = 0;
	c = va_arg(list, int);
	if ((param.flags & PF_FLAG_MINUS) == 0 && param.width > 1)
		count += pf_repeat(' ', param.width - 1);
	count += pf_write((char *)&c, 1);
	if ((param.flags & PF_FLAG_MINUS) != 0 && param.width > 1)
		count += pf_repeat(' ', param.width - 1);
	return (count);
}
