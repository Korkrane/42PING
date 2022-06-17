/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 20:03:27 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/17 13:44:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

static void init_time()
{
	params.time.min = 0;
	params.time.avg = 0;
	params.time.max = 0;
	params.time.total = 0;
}

void add_options_modification()
{
	if ((params.flags & s))
		params.packet_size = params.opts.packet_size;
	if ((params.flags & a))
		params.opts.bell = "\a";
	if (!(params.flags & f))
		params.interval = 1;
	if ((params.flags & i))
		params.interval = params.opts.interval;
	if (params.flags & t)
		params.ttl = params.opts.ttl;
}

void init_options()
{
	params.opts.count = 0;
	params.opts.interval = 0;
	params.opts.preload = 0;
	params.opts.ttl = 0;
	params.opts.deadline = 0;
	params.opts.packet_size = 0;
	params.opts.bell = "";
}

void init()
{
	init_time();
	init_options();
	params.packet_size = 56;
	params.sent_packets = 0;
	params.received_packets = 0;
	params.error_packets = 0;
	params.interval = 1;
	params.ttl = 64;
	params.process_id = getpid();
	params.seq = 1;
	params.socket_fd = -1;
	params.quit = 0;
}
