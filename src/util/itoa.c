/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 03:40:29 by pbondoer          #+#    #+#             */
/*   Updated: 2018/01/24 18:06:57 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "helpers.h"

static size_t		udigit_count(uintmax_t n, unsigned int base)
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

char				*pf_uitoa(uintmax_t n, unsigned int base, const char *dig,
						size_t precision)
{
	size_t		count;
	char		*str;

	count = udigit_count(n, base);
	if (count < precision)
		count = precision;
	str = pf_memalloc(count + 1);
	if (str == NULL)
		return (NULL);
	while (count > 0)
	{
		str[count - 1] = dig[n % base];
		count--;
		n /= base;
	}
	return (str);
}

static size_t		digit_count(intmax_t n, int base)
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

static inline char	*itoa_inner(int count, char sign, char neg, uintmax_t v)
{
	static char	*dig = "0123456789";
	char		*str;
	int			base;

	base = 10;
	str = pf_memalloc(count + neg + 1);
	if (str == NULL)
		return (NULL);
	if (sign)
		str[0] = sign;
	while (count > 0)
	{
		str[count + neg - 1] = dig[v % base];
		count--;
		v /= base;
	}
	return (str);
}

char				*pf_itoa(intmax_t n, t_pf_param param, char sign)
{
	int			count;
	char		neg;
	uintmax_t	v;

	neg = (n < 0 || sign ? 1 : 0);
	count = digit_count(n, 10);
	if (count < param.precision)
		count = param.precision;
	if (!(param.flags & PF_FLAG_MINUS) && (param.flags & PF_FLAG_ZERO)
			&& count < (int)param.width - neg)
	{
		count = (int)param.width - neg;
		if (param.precision > 0)
			count = param.precision;
	}
	v = (n < 0 ? -n : n);
	if (n < 0)
		sign = '-';
	return (itoa_inner(count, sign, neg, v));
}
