/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 03:30:26 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/17 06:20:51 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_handle_string(t_pf_param param, va_list list)
{
	char *str;
	size_t len;
	int count;

	count = 0;
	str = va_arg(list, char *);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str, INT_MAX);
	if (param.precision == -1)
		param.precision = INT_MAX;
	if (param.precision > (int)len)
		param.precision = len;
	count += pf_write_chunk(str, param.precision, ' ', param);
	return (count);
}

int			pf_write_chunk(const char *str, size_t len, char c,
						t_pf_param param)
{
	int		count;
	int		rem;

	count = 0;
	rem = 0;
	if ((param.conversion == 'x' || param.conversion == 'X') && 
			(param.flags & PF_FLAG_HASH) &&
			(param.value && *(uintmax_t *)param.value != 0))
		rem = 2;
	if (!(param.flags & PF_FLAG_ZERO) && !(param.flags & PF_FLAG_MINUS)
		&& param.width > len + rem)
		count += pf_repeat(c, param.width - len - rem);
	if ((param.conversion == 'x' || param.conversion == 'X') && 
			(param.flags & PF_FLAG_HASH) &&
			(param.value && *(uintmax_t *)param.value != 0))
		count += pf_write((param.conversion == 'x' ? "0x" : "0X"), 2);
	if ((param.flags & PF_FLAG_ZERO) && !(param.flags & PF_FLAG_MINUS)
		&& param.width > len + rem)
		count += pf_repeat(c, param.width - len - rem);
	count += pf_write(str, len);
	if ((param.flags & PF_FLAG_MINUS) && param.width > len + rem)
		count += pf_repeat(' ', param.width - len - rem);
	return (count);
}
