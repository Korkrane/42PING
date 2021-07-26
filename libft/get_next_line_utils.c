/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:24:58 by bahaas            #+#    #+#             */
/*   Updated: 2021/05/27 19:59:15 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

char	*ft_strnew(size_t size)
{
	char		*str;
	size_t		i;

	if (size <= 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i <= size)
		str[i++] = '\0';
	return (str);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char		*d;
	char		*s;

	d = (char *)dest;
	s = (char *)src;
	if (dest == src)
		return (dest);
	if (s < d)
	{
		while (len--)
			*(d + len) = *(s + len);
		return (dest);
	}
	while (len--)
		*d++ = *s++;
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*dest;
	int			size_s1;
	int			size_s2;
	int			size_total;

	if (!s1 && !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	size_total = size_s1 + size_s2;
	dest = ft_strnew(size_total);
	if (!dest)
	{
		free((char *)s1);
		return (NULL);
	}
	ft_memmove(dest, s1, size_s1);
	ft_memmove(dest + size_s1, s2, size_s2);
	dest[size_total] = '\0';
	free((char *)s1);
	return (dest);
}
