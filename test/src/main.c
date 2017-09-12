/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 22:15:40 by pbondoer          #+#    #+#             */
/*   Updated: 2017/02/08 02:30:12 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	test(char **argv, ...)
{
	va_list list;

	va_start(list, argv);
	parse_format(argv[1], list);
	va_end(list);
}

int		main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	test(argv, "salut", "bonjour", "bonsoir");
	return (0);
}
