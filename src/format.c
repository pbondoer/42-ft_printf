/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 03:35:56 by pbondoer          #+#    #+#             */
/*   Updated: 2017/05/01 02:31:19 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		param->field_width_access = width;
	}
	else
		param->field_width = width;
	return (0);
}

static int			handle_precision(t_pf_param *param, const char *str, size_t *i)
{
	int precision;

	if (str[*i] != '.')
		return (0);
	(*i)++;
	if (pf_atoi(str, 1, &precision, i))
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

t_pf_param			*get_param(const char *str, size_t len)
{
	static int		(*handle[6])(t_pf_param *, const char *, size_t *) = {
						handle_access, handle_flags, handle_width,
						handle_precision, handle_modifier, handle_conversion};
	static char		*error[6] = {"access", "flags", "width", "precision",
								"modifier", "conversion"};
	t_pf_param		*param;
	size_t			i;
	size_t			pos;

	i = 0;
	pos = 0;
	param = pf_param(str, len);
	while (i < 6)
	{
		printf(" -> %s at %zu\n", error[i], pos);
		if ((*handle[i])(param, str + 1, &pos))
		{
			//error
			printf(" --> error parsing %s at %zu\n", error[i], pos);
			break;
		}
		i++;
	}
	return (param);
	//end
}

t_pf_argument		*get_argument(const char *str, size_t start, size_t len,
									int is_valid)
{
	t_pf_argument	*arg;

	arg = ft_memalloc(sizeof(t_pf_argument));
	if (arg == NULL)
		return (NULL);
	arg->position = start;
	arg->length = len;
	if (*str == '%' && is_valid)
		arg->ptr = get_param(str, len);
	else
		arg->ptr = str;
	return (arg);
}

/*
** Parse a format string
** Returns a pointer to a linked argument list and the count
*/

t_pf_argument		*parse_format(const char *str)
{
	size_t			i;
	size_t			start;
	size_t			len;
	t_pf_argument	*arg;
	int				valid;

	i = 0;
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
			if (!valid)
				while (str[i] && str[i] != '%')
					i++;
			else
				i++;
		}
		else
			while (str[i] && str[i] != '%')
				i++;

		len = i - start;
		arg = get_argument(str + start, start, len, valid);
		if (valid)
		{
			t_pf_param param = *(t_pf_param *)arg->ptr;
			printf("parameter (start %zu len %zu): \"%s\"\n", start, len,
				ft_strsub(str, start, len));
			printf("access: %d\n", param.access);
			printf("flags: %d - ", param.flags);
			if ((param.flags & PF_FLAG_HASH) != 0) printf("HASH ");
			if ((param.flags & PF_FLAG_ZERO) != 0) printf("ZERO ");
			if ((param.flags & PF_FLAG_MINUS) != 0) printf("MINUS ");
			if ((param.flags & PF_FLAG_PLUS) != 0) printf("PLUS ");
			if ((param.flags & PF_FLAG_SPACE) != 0) printf("SPACE ");
			if ((param.flags & PF_FLAG_APOSTROPHE) > 0) printf("APOSTROPHE ");
			printf("\nwidth: %d\n", param.field_width);
			printf("width access: %d\n", param.field_width_access);
			printf("precision: %d\n", param.precision);
			printf("modifier: %d\n", param.modifier);
			printf("conversion: %c\n", param.conversion);
		}
	}

	return (arg);
}

/*
** Creates a printf param
** NOTE: All params are 0 at the start so no init is nescesary
*/

inline t_pf_param	*pf_param(const char *str, size_t len)
{
	t_pf_param	*param;

	param = ft_memalloc(sizeof(t_pf_param));
	if (param == NULL)
		return (NULL);
	param->str.str = str;
	param->str.length = len;
	return (param);
}
