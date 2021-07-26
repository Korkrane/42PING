/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 22:52:12 by bahaas            #+#    #+#             */
/*   Updated: 2021/05/27 19:55:51 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_length;
	size_t	dst_length;

	i = 0;
	src_length = ft_strlen(src);
	dst_length = ft_strlen(dst);
	if (size <= dst_length)
		return (src_length + size);
	while (src[i] && i + dst_length < size - 1)
	{
		dst[i + dst_length] = src[i];
		i++;
	}
	dst[i + dst_length] = '\0';
	return (src_length + dst_length);
}
