/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 02:09:04 by pbondoer          #+#    #+#             */
/*   Updated: 2017/10/17 07:33:44 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline extern int			pf_is_conversion(const char c)
{
	return (ft_strchr("dDioOuUxXeEfFgGaAcCsSpn%", c) != NULL);
}

inline extern int			pf_is_modifier(const char c)
{
	return (ft_strchr("hljz", c) != NULL);
}

inline extern int			pf_is_flag(const char c)
{
	return (ft_strchr("#0-+' ", c) != NULL);
}

inline extern int			pf_is_precision(const char c)
{
	return (ft_strchr("$*.", c) != NULL);
}

inline int					pf_is_valid(const char c)
{
	return (pf_is_conversion(c) || pf_is_modifier(c) || pf_is_flag(c) ||
			ft_isdigit(c) || pf_is_precision(c));
}
