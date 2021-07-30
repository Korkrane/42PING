/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 20:03:27 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/30 15:17:19 by bahaas           ###   ########.fr       */
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
	params.packet_size = 56;
	if((params.flags & s))
		params.packet_size = params.opts.packet_size;
	params.opts.bell = "";
	if((params.flags & a))
		params.opts.bell = "\a";
	params.sent_packets = 0;
	params.received_packets = 0;
	params.error_packets = 0;
	params.interval = 0;
	if(!(params.flags & f))
		params.interval = 1;
	if((params.flags & i))
		params.interval = params.opts.interval;
	params.ttl = 64;
	if(params.flags & t)
		params.ttl = params.opts.ttl;
	params.process_id = getpid();
	params.seq = 1;
	params.socket_fd = -1;
	params.quit = 0;
	ft_getadress(params.user_requested_address);
}
