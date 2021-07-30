/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:05:15 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/30 15:10:03 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"


void set_rtt_stats(double rtt)
{
	if(params.time.min == 0 || rtt < params.time.min)
		params.time.min = rtt;
	if(params.time.max == 0 || rtt > params.time.max)
		params.time.max = rtt;
	params.time.total += rtt;
	params.time.avg = params.time.total / params.received_packets;
}

double get_mdev()
{
	double mdev;
	double avg;
	double avg_square;

	avg = params.time.total / params.received_packets;
	avg_square = (params.time.total * params.time.total) / params.received_packets;
	mdev = sqrt(avg_square - (avg * avg));
	return (mdev);
}

int print_stats()
{
	long time;
	double mdev;

	time = get_elapsed_time(params.start);
	if(params.received_packets == 1)
		time = 0;
	printf("\n--- %s ping statistics ---\n", params.reversed_address);
	printf("%d packets transmitted, %d received, %d%% packet loss, time %ldms\n", params.sent_packets, params.received_packets, 0, time);
	printf("rtt min/avg/max/mdev = %.3lf/%.3lf/%.3lf/%.3lf ms\n", params.time.min, params.time.avg, params.time.max, get_mdev());
	return (true);
}
