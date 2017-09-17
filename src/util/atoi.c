/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 06:45:20 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/17 01:10:32 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_atoi(const char *str, int allow_neg, int *result, size_t *i)
{
	int nbr;
	int neg;

	neg = (str[*i] == '-');
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (allow_neg)
			(*i)++;
		else
			return (1);
	}
	nbr = 0;
	while (ft_isdigit(str[*i]))
	{
		nbr = nbr * 10 + (str[*i] - '0');
		(*i)++;
	}

	*result = (neg ? -nbr : nbr);
	return (0);
}
