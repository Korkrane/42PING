/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:51:06 by bahaas            #+#    #+#             */
/*   Updated: 2022/05/24 11:04:59 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
char		*ft_strlower(char *str)
{
    char *lower = ft_strdup(str);

    for(unsigned long i = 0; i < strlen(lower);i++)
        lower[i] = ft_tolower(lower[i]);
    //printf("%s\n", str);
    return lower;
}
