/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:02:40 by pbondoer          #+#    #+#             */
/*   Updated: 2018/01/24 18:02:53 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

/*
** Helper functions
*/

int				pf_atoi(const char *str, int allow_neg, int *result, size_t *i);
char			*ft_itoa(intmax_t n, t_pf_param param, char sign);
char			*ft_uitoa(uintmax_t n, unsigned int base, const char *digits,
					size_t precision);
void			*ft_memalloc(size_t size);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlen(const char *s, const size_t max);
int				ft_isdigit(int c);
char			*ft_strjoin(char *a, char *b);
int				pf_max(int a, int b);
int				pf_get_base(char c);
#endif
