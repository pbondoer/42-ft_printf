/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 22:22:58 by pbondoer          #+#    #+#             */
/*   Updated: 2018/01/24 18:02:35 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

# define PF_FLAG_NONE 0
# define PF_FLAG_HASH 1
# define PF_FLAG_ZERO 2
# define PF_FLAG_MINUS 4
# define PF_FLAG_PLUS 8
# define PF_FLAG_SPACE 16
# define PF_FLAG_APOSTROPHE 32

typedef struct	s_pf_string
{
	const char	*str;
	size_t		length;
}				t_pf_string;

typedef enum	e_pf_modifier
{
	NONE = 0, L = 1, H = 2, J = 3, Z = 4, LL = 5, HH = 6
}				t_pf_modifier;

typedef struct	s_pf_argument
{
	size_t			position;
	size_t			length;
	t_pf_string		str;
}				t_pf_argument;

typedef struct	s_pf_param
{
	t_pf_string		str;
	int				access;
	int				flags;
	unsigned int	width;
	int				width_access;
	int				precision;
	t_pf_modifier	modifier;
	char			conversion;
	int				error;
	void			*value;
}				t_pf_param;

/*
** Used when parsing formats and when doing the final substitution.
*/

typedef struct	s_pf_handle
{
	char			conversion;
	int				(*handle)(t_pf_param, va_list);
}				t_pf_handle;

/*
** Handlers
*/

int				pf_handle_percent(t_pf_param param, va_list list);
int				pf_handle_char(t_pf_param param, va_list list);
int				pf_handle_string(t_pf_param param, va_list list);
int				pf_handle_hex(t_pf_param param, va_list list);

int				pf_write_chunk(const char *str, int free, size_t len,
					t_pf_param param);

/*
** Core
*/

int				ft_printf(const char *format, ...);

int				pf_parse_format(const char *str, va_list list);
int				pf_transform(t_pf_param param, va_list list);

int				pf_write(const char *str, const size_t len);
int				pf_repeat(const char c, size_t len);

int				pf_is_conversion(const char c);
int				pf_is_modifier(const char c);
int				pf_is_flag(const char c);
int				pf_is_valid(const char c);
t_pf_param		pf_param(const char *str, const size_t len);
t_pf_string		pf_string(const char *str, size_t len);
t_pf_param		pf_get_param(const char *str, size_t len);

#endif
