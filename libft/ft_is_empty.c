/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:23:56 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/18 02:38:42 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_is_empty(char *str)
{
	int				i;

	i = 0;
	if (!str)
		return (TRUE);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
