/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 03:35:56 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/17 02:22:56 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int			handle_access(t_pf_param *param, const char *str, size_t *i)
{
	int access;
	int t;

	t = *i;
	if (!ft_isdigit(str[*i]))
		return (0);
	if (pf_atoi(str, 0, &access, i) || str[*i] != '$')
	{
		*i = t;
		return (0);
	}
	(*i)++;
	param->access = access;
	return (0);
}

static int			handle_flags(t_pf_param *param, const char *str, size_t *i)
{
	char c;

	while (*i < param->str.length)
	{
		c = str[*i];
		if (pf_is_flag(c))
		{
			if (c == '#')
				param->flags |= PF_FLAG_HASH;
			else if (c == '0')
				param->flags |= PF_FLAG_ZERO;
			else if (c == '-')
				param->flags |= PF_FLAG_MINUS;
			else if (c == '+')
				param->flags |= PF_FLAG_PLUS;
			else if (c == ' ')
				param->flags |= PF_FLAG_SPACE;
			else if (c == '\'')
				param->flags |= PF_FLAG_APOSTROPHE;
		}
		else
			return (0);
		(*i)++;
	}
	return (1); // too many flags
}

static int			handle_width(t_pf_param *param, const char *str, size_t *i)
{
	int width;
	int is_pos;

	if ((is_pos = (str[*i] == '*')))
		(*i)++;
	if (pf_atoi(str, 0, &width, i) && !is_pos)
		return (1);
	if (is_pos)
	{
		if (str[*i] == '$')
			(*i)++;
		else
			return (1);
		param->width_access = width;
	}
	else
		param->width = width;
	return (0);
}

static int			handle_precision(t_pf_param *param, const char *str, size_t *i)
{
	int precision;

	param->precision = -1;
	if (str[*i] != '.')
		return (0);
	param->precision = 0;
	(*i)++;
	if (pf_atoi(str, 0, &precision, i))
		return (1);
	param->precision = precision;
	return (0);
}

static int			handle_modifier(t_pf_param *param, const char *str, size_t *i)
{
	t_pf_modifier	m;

	if (!pf_is_modifier(str[*i]))
		return (0);
	if (str[*i] == 'l')
	{
		if (str[*i + 1] == 'l' && (*i)++)
			m = LL;
		else
			m = L;
	}
	if (str[*i] == 'h')
	{
		if (str[*i + 1] == 'h' && (*i)++)
			m = HH;
		else
			m = H;
	}
	if (str[*i] == 'j')
		m = J;
	else if (str[*i] == 'z')
		m = Z;
	(*i)++;
	param->modifier = m;
	return (0);
}

static int			handle_conversion(t_pf_param *param, const char *str, size_t *i)
{
	if (pf_is_conversion(str[*i]))
	{
		param->conversion = str[*i];
		(*i)++;
		return (0);
	}
	return (1);
}

t_pf_param			get_param(const char *str, size_t len)
{
	static int		(*handle[6])(t_pf_param *, const char *, size_t *) = {
						handle_access, handle_flags, handle_width,
						handle_precision, handle_modifier, handle_conversion};
	//static char		*error[6] = {"access", "flags", "width", "precision",
	//							"modifier", "conversion"};
	t_pf_param		param;
	size_t			i;
	size_t			pos;

	i = 0;
	pos = 0;
	param = pf_param(str, len);
	while (i < 6)
	{
		// printf(" -> %s at %zu\n", error[i], pos);
		if ((*handle[i])(&param, str + 1, &pos))
		{
			//error
			// printf(" --> error parsing %s at %zu\n", error[i], pos);
			param.error = 1;
			break;
		}
		i++;
	}

	/*
	printf("\nparameter: \"%.*s\"\n", (int)len, str);
	printf("access: %d\n", param.access);
	printf("flags: %d -> ", param.flags);
	if ((param.flags & PF_FLAG_HASH) != 0) printf("HASH ");
	if ((param.flags & PF_FLAG_ZERO) != 0) printf("ZERO ");
	if ((param.flags & PF_FLAG_MINUS) != 0) printf("MINUS ");
	if ((param.flags & PF_FLAG_PLUS) != 0) printf("PLUS ");
	if ((param.flags & PF_FLAG_SPACE) != 0) printf("SPACE ");
	if ((param.flags & PF_FLAG_APOSTROPHE) > 0) printf("APOSTROPHE ");
	printf("\nwidth: %d\n", param.width);
	printf("width access: %d\n", param.width_access);
	printf("precision: %d\n", param.precision);
	printf("modifier: %d\n", param.modifier);
	printf("conversion: %c\n", param.conversion);
	*/

	return (param);
}

int		get_argument(const char *str, size_t len, int is_valid, va_list list)
{
	//t_pf_argument	*arg;

	//arg = ft_memalloc(sizeof(t_pf_argument));
	//if (arg == NULL)
	//	return (NULL);
	//arg->position = start;
	//arg->length = len;
	if (*str == '%' && is_valid)
		return (pf_transform(get_param(str, len), list));
	else
		return (pf_write(str, len));
}

/*
** Parse a format string and prints stuff
*/

int		pf_parse_format(const char *str, va_list list)
{
	size_t			i;
	size_t			start;
	size_t			len;
	int				valid;
	int				count;

	i = 0;
	count = 0;
	while (str[i])
	{
		start = i;
		valid = 0;
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			while (str[i] && pf_is_valid(str[i]) && !pf_is_conversion(str[i]))
				i++;
			valid = pf_is_valid(str[i]);
			if (valid)
				i++;
			else
				while (str[i] && str[i] != '%')
					i++;
		}
		else
			while (str[i] && str[i] != '%')
				i++;

		len = i - start;
		count += get_argument(str + start, len, valid, list);

		//if (!valid)
		//	printf("\n---> string from start %zu len %zu\n\n", start, len);
	}
	return (count); // TODO: return the count of characters
}

/*
** Creates a printf param
** NOTE: All params are 0 at the start so no init is nescesary
*/

inline t_pf_param	pf_param(const char *str, size_t len)
{
	t_pf_param	param;

	param = (t_pf_param) {
		.str = (t_pf_string){ .str = str, .length = len },
		.access = 0,
		.flags = 0,
		.width = 0,
		.width_access = 0,
		.precision = 0,
		.modifier = NONE,
		.conversion = 0,
		.error = 0
	};

	return (param);
}

inline t_pf_string	pf_string(const char *str, size_t len)
{
	return ((t_pf_string) {
		.str = str,
		.length = len
	});
}
