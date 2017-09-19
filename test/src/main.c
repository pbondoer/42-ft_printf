/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 22:15:40 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/19 05:42:05 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	//char *f = "%s -->%<--\n";

	//ft_printf(f, "ft", f);
	//printf   (f, "pf", f);
	char *f = "% Zoooo\n";
	ft_printf(f);
	printf(f);
	return (0);
}
