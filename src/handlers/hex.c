/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 03:51:49 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/18 05:27:41 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline static int		get_base(char c)
{
	if (c == 'X' || c == 'x')
		return (16);
	else if (c == 'o')
		return (8);
	else
		return (10);
}

inline static int		s_handle(t_pf_param param, va_list list)
{
	intmax_t		n;
	char			*str;
	int				count;
	char			sign;

	count = 0;
	if (param.modifier == L)
		n = va_arg(list, long);
	else if (param.modifier == LL)
		n = va_arg(list, long long);
	else if (param.modifier == J)
		n = va_arg(list, intmax_t);
	else
		n = va_arg(list, int);
	if (param.modifier == H)
		n = (short)n;
	else if (param.modifier == HH)
		n = (char)n;
	param.value = &n;
	if (param.flags & PF_FLAG_PLUS)
		sign = '+';
	else if (param.flags & PF_FLAG_SPACE)
		sign = ' ';
	else
		sign = '\0';
	
	if (param.precision == 0 && n == 0)
		str = "";
	else
		str = ft_itoa(n, 10, "0123456789",
				(param.precision > 0 ? param.precision : 0), sign);
	count += pf_write_chunk(str, ft_strlen(str, INT_MAX),
			(param.flags & PF_FLAG_ZERO ? '0' : ' '), param);
	return (count);
}

int					pf_handle_hex(t_pf_param param, va_list list)
{
	uintmax_t		n;
	char			*str;
	int				count;
	int				base;

	if (param.conversion == 'd')
		return (s_handle(param, list));
	base = get_base(param.conversion);
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
	if (param.precision == 0 && n == 0)
		str = "";
	else
		str = ft_uitoa(n, base, (param.conversion == 'X' ? "0123456789ABCDEF" :
				"0123456789abcdef"), (param.precision > 0 ? param.precision : 0));
	count += pf_write_chunk(str, ft_strlen(str, INT_MAX),
			(param.flags & PF_FLAG_ZERO ? '0' : ' '), param);
	return (count);
}
