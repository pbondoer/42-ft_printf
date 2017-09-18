/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 03:40:29 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/18 05:26:11 by pbondoer         ###   ########.fr       */
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

	i = 1;
	if (n < 0)
		n = -n;
	while (n >= base)
	{
		i++;
		n /= base;
	}
	return (i);
}

char			*ft_itoa(intmax_t n, int base, const char *digits,
							size_t precision, char sign)
{
	size_t		count;
	char		*str;
	char		neg;

	neg = (n < 0 || sign ? 1 : 0);
	count = digit_count(n, base);
	if (count < precision)
		count = precision;
	str = ft_memalloc(count + neg + 1);
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		sign = '-';
	}
	if (sign)
		str[0] = sign;
	while (count > 0)
	{
		str[count + neg - 1] = digits[n % base];
		count--;
		n /= base;
	}
	return (str);
}
