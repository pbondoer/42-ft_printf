/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 22:22:58 by pbondoer          #+#    #+#             */
/*   Updated: 2017/02/08 07:41:42 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# include <stdio.h>

# define PF_FLAG_NONE 0
# define PF_FLAG_HASH 1
# define PF_FLAG_ZERO 2
# define PF_FLAG_MINUS 4
# define PF_FLAG_PLUS 8
# define PF_FLAG_SPACE 16
# define PF_FLAG_APOSTROPHE 32

/*
** Used when parsing formats and when doing the final substitution.
*/

typedef enum	e_pf_modifier
{
	NONE = 0, L = 1, H = 2, J = 3, Z = 4, LL = 5, HH = 6
}				t_pf_modifier;

typedef struct	s_pf_argument
{
	size_t		position;
	size_t		length;
}				t_pf_argument;

typedef struct	s_pf_string
{
	char		*str;
	size_t		length;
}				t_pf_string;

typedef struct	s_pf_param
{
	t_pf_string		str;
	t_pf_argument	arg;
	int				access;
	int				flags;
	int				field_width;
	int				field_width_access;
	int				precision;
	t_pf_modifier	modifier;
	char			conversion;
}				t_pf_param;

int				ft_printf(const char *format, ...);
void			parse_format(const char *str);
int				pf_is_conversion(const char c);
int				pf_is_modifier(const char c);
int				pf_is_flag(const char c);
int				pf_is_valid(const char c);
t_pf_param		pf_param(const size_t pos, const size_t len);

/*
** Helper functions
*/

int				pf_atoi(const char *str, int allow_neg, int *result, size_t *i);
#endif
