/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 03:51:49 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/17 06:00:50 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					pf_handle_hex(t_pf_param param, va_list list)
{
	uintmax_t		n;
	char			*str;
	int				count;

	count = 0;
	if (param.modifier == L)
		n = va_arg(list, unsigned long);
	else if (param.modifier == LL)
		n = va_arg(list, unsigned long long);
	else if (param.modifier == J)
		n = va_arg(list, uintmax_t);
	else
		n = va_arg(list, unsigned int);
	param.value = &n;
	str = ft_uitoa(n, 16, (param.conversion == 'X' ? "0123456789ABCDEF" :
				"0123456789abcdef")); // TODO: free
	count += pf_write_chunk(str, ft_strlen(str, INT_MAX),
			(param.flags & PF_FLAG_ZERO ? '0' : ' '), param);
	return (count);
}
