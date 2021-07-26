/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 22:52:07 by bahaas            #+#    #+#             */
/*   Updated: 2021/05/27 19:57:44 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new_array;

	new_array = NULL;
	new_array = malloc(nmemb * sizeof(size));
	if (!new_array)
		return (NULL);
	ft_bzero(new_array, nmemb * size);
	return (new_array);
}
