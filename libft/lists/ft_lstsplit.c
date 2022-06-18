/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:18:19 by bahaas            #+#    #+#             */
/*   Updated: 2020/10/02 15:18:24 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstsplit(char const *s, char c)
{
	t_list		*dest;
	char		**tab;

	dest = NULL;
	tab = ft_split(s, c);
	if (tab)
	{
		while (*tab)
		{
			ft_lstadd_back(&dest, ft_lstnew(*tab));
			tab++;
		}
	}
	return (dest);
}
