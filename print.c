/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:16:53 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/18 02:29:09 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

void printTimestamp()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    printf("[%ld.%ld] ", tv.tv_sec, tv.tv_usec);
}

void printPingInfo()
{
    printf("PING %s (%s) %lu(%zu) bytes of data.\n",
           params.reversed_address,
           params.address,
           sizeof(t_packet) - sizeof(struct icmphdr),
           sizeof(t_packet) - sizeof(struct icmphdr)  + sizeof(struct icmp));
}

void printReplyInfos(t_reply reply, double time)
{
    short reply_ttl;
    struct ip *packet_content;

    packet_content = (struct ip *)reply.receive_buffer;
    reply_ttl = (short)packet_content->ip_ttl;
    if (!hasOptionEnabled(q))
    {
        if (hasOptionEnabled(D))
            printTimestamp();
        if (hasOptionEnabled(f))
            printf("\b");
        else
        {
            if (ft_strcmp(params.address, params.requestedAddress) && !(hasOptionEnabled(n)))
                printf("%lu bytes from %s (%s): icmp_seq=%d ttl=%d time=%.2lf ms\n", reply.received_bytes - sizeof(struct ip), params.reversed_address, params.address, params.seq, reply_ttl, time);
            else
                printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%.2lf ms\n", reply.received_bytes - sizeof(struct ip), params.address, params.seq, reply_ttl, time);

            if(hasOptionEnabled(a))
                printf("\a");
        }
    }
    setRTTstats(time);
}

void printStats()
{
	long time;
	double receivedPerc = 100 - (params.received_packets / params.sent_packets * 100);
	time = getElapsedTime(params.start);
	if(params.received_packets == 1)
		time = 0;
	printf("\n--- %s ping statistics ---\n", params.reversed_address);
	printf("%d packets transmitted, %d received, %f%% packet loss, time %ldms\n", params.sent_packets, params.received_packets, receivedPerc, time);
	printf("rtt min/avg/max/mdev = %.3lf/%.3lf/%.3lf/%.3lf ms\n", params.time.min, params.time.avg, params.time.max, getMdev());
}