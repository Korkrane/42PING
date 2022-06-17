/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:51:06 by bahaas            #+#    #+#             */
/*   Updated: 2022/05/24 10:52:51 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strupper(char *str)
{
    char *upper = str;

    for(unsigned long i = 0; i < strlen(upper);i++)
        upper[i] = ft_toupper(upper[i]);
    return upper;
}
