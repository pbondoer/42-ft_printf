/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 03:30:26 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/18 05:19:25 by pbondoer         ###   ########.fr       */
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

inline static void	set_prefix(t_pf_param param, int *rem, char **prefix)
{
	if ((!(param.flags & PF_FLAG_HASH) ||
			!(param.value && *(uintmax_t *)param.value != 0))
			&& !((param.flags & PF_FLAG_HASH) && param.conversion == 'o'))
		return;
	if ((param.conversion == 'x' || param.conversion == 'X'))
	{
		*rem = 2;
		*prefix = (param.conversion == 'x' ? "0x" : "0X");
	}
	if (param.conversion == 'o')
	{
		*rem = 1;
		*prefix = "0";
	}
}

int			pf_write_chunk(const char *str, size_t len, char c,
						t_pf_param param)
{
	int		count;
	int		rem;
	char	*prefix;

	count = 0;
	rem = 0;
	set_prefix(param, &rem, &prefix);
	if (!(param.flags & PF_FLAG_ZERO) && !(param.flags & PF_FLAG_MINUS)
		&& param.width > len + rem)
		count += pf_repeat(c, param.width - len - rem);
	if (rem)
		count += pf_write(prefix, rem);
	if ((param.flags & PF_FLAG_ZERO) && !(param.flags & PF_FLAG_MINUS)
		&& param.width > len + rem)
		count += pf_repeat(c, param.width - len - rem);
	count += pf_write(str, len);
	if ((param.flags & PF_FLAG_MINUS) && param.width > len + rem)
		count += pf_repeat(' ', param.width - len - rem);
	return (count);
}
