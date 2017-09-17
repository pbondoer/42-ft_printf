/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 01:31:24 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/17 02:23:58 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
** TODO: Change this to use a buffer system
*/

int			pf_write(const char *str, const size_t len)
{
	write(1, str, len);
	return (len);
}

int			pf_repeat(const char c, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		pf_write(&c, 1);
		i++;
	}
	return (len);
}
