/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 03:30:26 by pbondoer          #+#    #+#             */
/*   Updated: 2018/01/24 18:08:42 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "helpers.h"

int					pf_handle_string(t_pf_param param, va_list list)
{
	char	*str;
	size_t	len;
	int		count;

	count = 0;
	str = va_arg(list, char *);
	if (str == NULL)
		str = "(null)";
	len = pf_strlen(str, INT_MAX);
	if (param.precision == -1)
		param.precision = INT_MAX;
	if (param.precision > (int)len)
		param.precision = len;
	count += pf_write_chunk(str, 0, param.precision, param);
	return (count);
}

inline static void	set_prefix(t_pf_param param, int *rem, char **prefix)
{
	if ((!(param.flags & PF_FLAG_HASH) ||
			(param.value && *(uintmax_t *)param.value == 0))
			&& !((param.flags & PF_FLAG_HASH) && param.conversion == 'o')
			&& !(param.conversion == 'p'))
		return ;
	if (param.conversion == 'x' || param.conversion == 'X' ||
			param.conversion == 'p')
	{
		*rem = 2;
		*prefix = (param.conversion == 'X' ? "0X" : "0x");
	}
	if (param.conversion == 'o')
	{
		*rem = 1;
		*prefix = "0";
	}
}

int					pf_write_chunk(const char *str, int f, size_t len,
						t_pf_param param)
{
	int		count;
	int		rem;
	char	*prefix;
	char	p;

	count = 0;
	rem = 0;
	p = (param.conversion != 'd' && param.flags & PF_FLAG_ZERO ? '0' : ' ');
	set_prefix(param, &rem, &prefix);
	if (param.conversion == 'o' && str && str[0] == '0')
		rem = 0;
	param.width -= rem;
	if (!(param.flags & PF_FLAG_MINUS) && param.width > len)
		count += pf_repeat(p, param.width - len);
	if (rem)
		count += pf_write(prefix, rem);
	count += pf_write(str, len);
	if ((param.flags & PF_FLAG_MINUS) && param.width > len)
		count += pf_repeat(' ', param.width - len);
	if (f)
		free((void *)str);
	return (count);
}
