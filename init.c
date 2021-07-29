/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 20:03:27 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/29 15:57:35 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

static void	init_time()
{
	params.time.min = 0;
	params.time.avg = 0;
	params.time.max = 0;
	params.time.total = 0;
}

//doesnt work with -c 4 www.42.fr cuz stuck on 4
char	*get_host(int ac, char **av)
{
	for(int i = 1; i < ac; i++)	
	{
		if(av[i][0] == '-' && av[i][1] != '\0')
			i++;
		else
		{
			printf("av : %s\n", av[i]);
			return (av[i]);
		}
	}
	return (NULL);
}

void	init(int ac, char **av)
{
	init_time();
	params.sent_packets = 0;
	params.received_packets = 0;
	params.error_packets = 0;
	params.interval = 0;
	if(!(params.flags & F))
		params.interval = 1;
	if((params.flags & I))
		params.interval = params.opts.interval;
	params.ttl = 64;
	if(params.flags & T)
		params.ttl = params.opts.ttl;
	params.process_id = getpid();
	params.seq = 1;
	params.socket_fd = -1;
	params.quit = 0;
	ft_getadress(params.user_requested_address);
}

void	init_packet(struct s_packet *packet, struct timeval current_time)
{
	ft_bzero(packet, sizeof(t_packet));
	packet->icmp_header.icmp_type = ICMP_ECHO;
	packet->icmp_header.icmp_code = 0;
	packet->icmp_header.icmp_seq = BSWAP16(params.seq);
	packet->icmp_header.icmp_id = BSWAP16(params.process_id);
	ft_memcpy(&packet->icmp_header.icmp_dun, &(current_time.tv_sec), sizeof(current_time.tv_sec));
	packet->icmp_header.icmp_cksum = checksum(packet, sizeof(*packet));
}


void init_reply(t_reply *reply)
{
	ft_bzero(reply, sizeof(t_reply));
	reply->iov.iov_base = reply->receive_buffer;
	reply->iov.iov_len = sizeof(reply->receive_buffer);
	reply->msghdr.msg_name = params.address;
	reply->msghdr.msg_iov = &reply->iov;
	reply->msghdr.msg_iovlen = 1;
	reply->msghdr.msg_control = &reply->control;
	reply->msghdr.msg_controllen = sizeof(reply->control);
}


