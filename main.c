/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 16:53:09 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/30 15:28:20 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"


static int help()
{
	printf("Usage: ping [-aAbBdDfhLnOqrRUvV64] [-c count] [-i interval] [-I interface]\n"
			"\t    [-m mark] [-M pmtudisc_option] [-l preload] [-p pattern] [-Q tos]\n"
			"\t    [-s packetsize] [-S sndbuf] [-t ttl] [-T timestamp_option]\n"
			"\t    [-w deadline] [-W timeout] [hop1 ...] destination\n");
	printf("Usage: ping -6 [-aAbBdDfhLnOqrRUvV64] [-c count] [-i interval] [-I interface]\n"
			"\t     [-l preload] [-m mark] [-M pmtudisc_option]\n"
			"\t     [-N nodeinfo_option] [-p pattern] [-Q tclass] [-s packetsize]\n"
			"\t     [-S sndbuf] [-t ttl] [-T timestamp_option] [-w deadline]\n"
			"\t     [-W timeout] destination\n");
	return (0);
}

void	error_output(char *message)
{
	fprintf(stderr, "%s\n", message);
}

void	error_output_and_exit(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void ft_getadress(char *host_name)
{
	struct addrinfo hints;
	struct addrinfo *res = NULL;
	char address[INET_ADDRSTRLEN];

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_CANONNAME;
	if(getaddrinfo(host_name, NULL, &hints, &res) != 0)
	{
		printf("error in getaddress\n");
		return ;
	}
	params.reversed_address = res->ai_canonname;
	ft_memcpy(&params.sockaddr, res->ai_addr, sizeof(struct sockaddr_in));
	inet_ntop(AF_INET, &(params.sockaddr.sin_addr), address, INET_ADDRSTRLEN);
	params.address = ft_strdup(address);
}

void check_D_opt()
{
		if(params.flags & D)
		{
			struct timeval tv;
			gettimeofday(&tv, NULL);
			printf("[%ld.%ld]", tv.tv_sec, tv.tv_usec);
		}
}

void	display_sequence(double start, double end, t_reply reply, struct timeval start_timestamp, struct timeval end_timestamp)
{
	short		reply_ttl;
	double		time_elapsed;
	struct ip	*packet_content;

	packet_content = (struct ip *)reply.receive_buffer;
	reply_ttl = (short)packet_content->ip_ttl;
	time_elapsed = calculate_elapsed_time(start_timestamp, end_timestamp);
	double time_elapss = end - start;
	printf("time_elapsed tho: %lf\n", time_elapss);
	if(!(params.flags & q))
	{
		check_D_opt();
		if(!(params.flags & f))
		{
			if (ft_strcmp(params.address, params.user_requested_address) && !(params.flags & n))
				printf("%lu bytes from %s (%s): icmp_seq=%d ttl=%d time=%.3lf ms%s\n", reply.received_bytes - sizeof(struct ip),
						params.reversed_address, params.address, params.seq, reply_ttl, time_elapsed, params.opts.bell);
			else if(params.flags & n) //bonus -n
				printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%.3lf ms%s\n", reply.received_bytes - sizeof(struct ip),
						params.address, params.seq, reply_ttl, time_elapsed, params.opts.bell);
			else
				printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%.3lf ms%s\n", reply.received_bytes - sizeof(struct ip),
						params.address, params.seq, reply_ttl, time_elapsed, params.opts.bell);
		}
		else
		{
			ft_putchar_fd('\b', 1);
			fflush(stdout);
		}
	}
	set_rtt_stats(time_elapsed);
}

void			wait_interval(struct timeval start)
{
	struct timeval	current_time;
	struct timeval	goal_time;

	if (params.interval)
	{
		current_time = start;
		goal_time.tv_sec = current_time.tv_sec + (long)params.interval;
		goal_time.tv_usec = current_time.tv_usec + (long)((params.interval - (long)params.interval) * 1000000);
		while (timercmp(&current_time, &goal_time, <))
			set_time(&current_time);
	}
}

int check_c_opt()
{
		if(params.opts.count)
		{
			params.opts.count--;
			if(!params.opts.count)
				return(print_stats());
		}	
		return (false);
}

void			ping_loop(void)
{
	t_packet			packet;
	struct timeval		current_start_timestamp;
	struct timeval		current_ending_timestamp;
	double start;
	double end;

	while(!params.quit)
	{
		start = get_time();
		set_time(&current_start_timestamp);
		init_packet(&packet, current_start_timestamp);
		if (send_packet(&packet))
		{
			init_reply(&params.reply);
			if (receive_reply(&params.reply))
			{
				params.received_packets++;
				end = get_time();
				set_time(&current_ending_timestamp);
				display_sequence(start, end, params.reply, current_start_timestamp, current_ending_timestamp);;
			}
			else if (receive_reply(&params.reply) == TTL_EXCEEDED_CODE)
			{
				//		display_exceeded_sequence(reply);
				//		params.error_packets++;
			}
		}
		if(check_c_opt())
			break;
		params.seq++;
		params.opts.preload - 1 > 0 ? params.opts.preload-- : wait_interval(current_start_timestamp);
	}
}

int parsing(int ac, char **av)
{
	if(ac < 2)
		return(help());
	for(int i = 1; i < ac; i++)
	{
		if(av[i][0] == '-')
		{
			int flag = 1;
			for(int j = 1; av[i][j] && flag; j++)
			{
				switch (av[i][j])
				{
					case 'v': case 'D': case 'n': case 'f': case 'a': case 'q': 
						add_no_params_opt(av[i][j]);
						break;
					case 'h':
						return(help());
					case 'c': case 'i': case 'l': case 't': case 'w': case 's':
						add_params_opt(av, &i, j, &flag);
						break;
					default:
						printf("ping: Invalid option -- '%c'\n", av[i][j]);
						return(help());
				}
			}
		}
		else
		{
			params.user_requested_address = av[i];
			_checkOpt();
			return (true);
		}
	}
	return (true);
}

int		main(int ac, char **av)
{
	if (parsing(ac, av))
	{
		init(ac, av);
		set_signal();
		if (params.address)
			create_socket();
		if (params.socket_fd != -1)
		{
			printf("PING %s (%s) %d(%d) bytes of data.\n", params.reversed_address, params.address, params.packet_size, params.packet_size + 28);
			params.start = get_time();
			ping_loop();
		}
	}
	return (0);
}
