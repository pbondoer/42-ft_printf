/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 22:15:40 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/18 03:28:02 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	//if (argc < 2)
	//	return (1);

	(void)argc;
	(void)argv;
//	printf(argv[1], "salut", "bonjour", "bonsoir");
//	printf("\n");
//	ft_printf(argv[1], "salut", "bonjour", "bonsoir");
//	ft_printf("\n");
	ft_printf("ft    : %.x %#.x\n", 42, 42);
	printf   ("printf: %.x %#.x\n", 42, 42);
	return (0);
}
