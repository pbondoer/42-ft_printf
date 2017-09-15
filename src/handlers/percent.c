/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 18:53:18 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/14 20:07:34 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_pf_string		pf_handle_percent(t_pf_param param, va_list list)
{
	t_pf_string	pf;

	(void)param;
	(void)list;
	pf.str = "%";
	pf.length = 1;

	return (pf);
}
