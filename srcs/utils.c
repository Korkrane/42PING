/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 22:27:26 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/18 04:13:00 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

int hasOptionEnabled(int opt)
{
    if(params.flags & opt)
        return true;
    return false;
}

int hasReachedCountLimit()
{
        params.opts.count--;
        if (params.opts.count == 0)
        {
            printStats();
            return true;
        }
    return false;
}