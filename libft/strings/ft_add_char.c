/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 07:54:00 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/18 02:38:03 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_add_char(char *str, char c)
{
	char	*new;
	int		len;

	len = ft_strlen(str);
	new = ft_strnew(len + 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, str, len);
	new[len] = c;
	ft_strdel(&str);
	return (new);
}
