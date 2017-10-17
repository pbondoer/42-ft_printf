/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 00:26:36 by pbondoer          #+#    #+#             */
/*   Updated: 2017/10/17 07:35:12 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern inline void		*ft_memalloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	while (size > 0)
	{
		size--;
		((unsigned char *)ptr)[size] = (unsigned char)0;
	}
	return (ptr);
}

extern inline char		*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

extern inline size_t	ft_strlen(const char *s, const size_t max)
{
	size_t i;

	i = 0;
	while (s[i] && i < max)
		i++;
	return (i);
}

extern inline int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

extern inline char		*ft_strjoin(char *a, char *b)
{
	char	*ret;
	int		i;

	ret = ft_memalloc(ft_strlen(a, INT_MAX) + ft_strlen(b, INT_MAX) + 1);
	i = 0;
	while (*a)
		ret[i++] = *(a++);
	while (*b)
		ret[i++] = *(b++);
	return (ret);
}
