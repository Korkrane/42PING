/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 20:03:27 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/09 19:39:11 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

static void init_time(t_params *params)
{
    params->time.min = 0;
    params->time.avg = 0;
    params->time.max = 0;
    params->time.total = 0;
}

void init(int ac, char **av, t_params *params)
{
    init_time(params);
    params->packet_size = 56;
    if ((params->flags & s))
        params->packet_size = params->opts.packet_size;
    params->opts.bell = "";
    if ((params->flags & a))
        params->opts.bell = "\a";
    params->sent_packets = 0;
    params->received_packets = 0;
    params->error_packets = 0;
    params->interval = 0;
    if (!(params->flags & f))
        params->interval = 1;
    if ((params->flags & i))
        params->interval = params->opts.interval;
    params->ttl = 64;
    if (params->flags & t)
        params->ttl = params->opts.ttl;
    params->process_id = getpid();
    params->seq = 1;
    params->socket_fd = -1;
    params->quit = 0;
    ft_getadress(params->user_requested_address, params);
}
