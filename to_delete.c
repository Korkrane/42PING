/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 22:27:42 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/09 19:25:24 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

void _checkOpt(t_params params)
{
    printf("OPT CHECK :\n");
    if (params.flags & D)
        printf("D opt enabled\n");
    if (params.flags & v)
        printf("v opt enabled\n");
    if (params.flags & n)
        printf("n opt enabled\n");
    if (params.flags & f)
        printf("f opt enabled\n");
    if (params.flags & a)
        printf("a opt enabled\n");
    if (params.flags & q)
        printf("q opt enabled\n");
    if (params.flags & c)
        printf("c opt enabled\n");
    if (params.flags & i)
        printf("i opt enabled\n");
    if (params.flags & l)
        printf("l opt enabled\n");
    if (params.flags & t)
        printf("t opt enabled\n");
    if (params.flags & w)
        printf("w opt enabled\n");
    if (params.flags & s)
        printf("s opt enabled\n");
}
