/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:02:40 by pbondoer          #+#    #+#             */
/*   Updated: 2018/01/24 18:07:27 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

/*
** Helper functions
*/

int				pf_atoi(const char *str, int allow_neg, int *result, size_t *i);
char			*pf_itoa(intmax_t n, t_pf_param param, char sign);
char			*pf_uitoa(uintmax_t n, unsigned int base, const char *digits,
					size_t precision);
void			*pf_memalloc(size_t size);
char			*pf_strchr(const char *s, int c);
size_t			pf_strlen(const char *s, const size_t max);
int				pf_isdigit(int c);
char			*pf_strjoin(char *a, char *b);
int				pf_max(int a, int b);
int				pf_get_base(char c);
#endif
