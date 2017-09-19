/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 03:40:29 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/19 04:49:25 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	udigit_count(uintmax_t n, unsigned int base)
{
	size_t i;

	i = 1;
	while (n >= base)
	{
		i++;
		n /= base;
	}
	return (i);
}

char			*ft_uitoa(uintmax_t n, unsigned int base, const char *digits,
						size_t precision)
{
	size_t		count;
	char		*str;

	count = udigit_count(n, base);
	if (count < precision)
		count = precision;
	str = ft_memalloc(count + 1);
	if (str == NULL)
		return (NULL);
	while (count > 0)
	{
		str[count - 1] = digits[n % base];
		count--;
		n /= base;
	}
	return (str);
}

static size_t	digit_count(intmax_t n, int base)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		i++;
		n /= base;
	}
	return (i);
}

char			*ft_itoa(intmax_t n, int base, const char *digits,
							t_pf_param param, char sign)
{
	int			count;
	char		*str;
	char		neg;
	uintmax_t	v;

	neg = (n < 0 || sign ? 1 : 0);
	count = digit_count(n, base);
	if (count < param.precision)
		count = param.precision;
	if (!(param.flags & PF_FLAG_MINUS) && (param.flags & PF_FLAG_ZERO)
			&& count < (int)param.width - neg)
	{
		count = (int)param.width - neg;
		if (param.precision > 0)
			count = param.precision;
	}
	str = ft_memalloc(count + neg + 1);
	if (str == NULL)
		return (NULL);
	v = (n < 0 ? -n : n);
	if (n < 0)
		sign = '-';
	if (sign)
		str[0] = sign;
	while (count > 0)
	{
		str[count + neg - 1] = digits[v % base];
		count--;
		v /= base;
	}
	return (str);
}
