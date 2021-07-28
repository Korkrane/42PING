/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 16:53:09 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/28 19:38:35 by bahaas           ###   ########.fr       */
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

double	get_time(void)
{
	struct timeval	tv;
	double			end;

	gettimeofday(&tv, NULL);
	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (end);
}

double	elapsed_time(double starter)
{
	struct timeval	tv;
	double			end;

	gettimeofday(&tv, NULL);
	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (end - starter);
}

void set_rtt_stats(double rtt)
{
	if(ping.time.min == 0 || rtt < ping.time.min)
		ping.time.min = rtt;
	if(ping.time.max == 0 || rtt > ping.time.max)
		ping.time.max = rtt;
	ping.time.total += rtt;
	ping.time.avg = ping.time.total / ping.received_packets;
}

double get_mdev()
{
	double mdev;
	double avg;
	double avg_square;

	avg = ping.time.total / ping.received_packets;
	avg_square = (ping.time.total * ping.time.total) / ping.received_packets;
	mdev = sqrt(avg_square - (avg * avg));
	return (mdev);
}

void print_stats()
{
	long time;
	double mdev;

	time = elapsed_time(ping.start);
	if(ping.received_packets == 1)
		time = 0;
	printf("\n--- %s ping statistics ---\n", ping.reversed_address);
	printf("%d packets transmitted, %d received, %d%% packet loss, time %ldms\n", ping.sent_packets, ping.received_packets, 0, time);
	printf("rtt min/avg/max/mdev = %.3lf/%.3lf/%.3lf/%.3lf ms\n", ping.time.min, ping.time.avg, ping.time.max, get_mdev());
}

void sig_int()
{
	ping.quit = 1;
	print_stats();
}

void sig_quit()
{
	ping.quit = 1;
}

void sig_handler(int code)
{
	if(code == SIGINT)
		sig_int();
	else if(code == SIGQUIT)
		sig_quit();
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
	ping.reversed_address = res->ai_canonname;
	ft_memcpy(&ping.sockaddr, res->ai_addr, sizeof(struct sockaddr_in));
	inet_ntop(AF_INET, &(ping.sockaddr.sin_addr), address, INET_ADDRSTRLEN);
	ping.address = ft_strdup(address);
//	printf("address: %s\n", ping.address);
//	printf("reversed_address: %s\n", ping.reversed_address);
}

void	init_time()
{
	ping.time.min = 0;
	ping.time.avg = 0;
	ping.time.max = 0;
	ping.time.total = 0;
}

void	init(char **av)
{
	/*
	   ping.ttl = 64;
	//ping.count = 0;
	//ping.interval = 1;
	ping.process_id = getpid();
	ping.seq = 1;
	//ping.sent_packets = 0;
	//ping.received_packets = 0;
	//ping.error_packets = 0;
	ping.socket_fd = -1;
	ping.quit = 0;
	//ping.sum_time = 0;
	//ping.max_time = 0;
	//ping.min_time = 0;
	//ping.square_sum_time = 0;
	get_address(&(ping.user_requested_address), argv);
	interpret_address(ping.user_requested_address);
	printf("ping.user_requested_address : %s\n", ping.user_requested_address);
	*/
	init_time();
	ping.interval = 1;
	ping.ttl = 64;
	ping.process_id = getpid();
	ping.seq = 1;
	ping.socket_fd = -1;
	ping.quit = 0;
	ft_getadress(av[1]);
	ping.user_requested_address = av[1];
//	printf("ping.user_requested_address : %s\n", ping.user_requested_address);
}

void	create_socket(void)
{
	int				socket_fd;
	struct timeval	timeout;

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	if ((socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
		error_output_and_exit(SOCKET_ERROR);
	if ((setsockopt(socket_fd, IPPROTO_IP, IP_TTL, &(ping.ttl), sizeof(ping.ttl))) == -1)
		error_output_and_exit(SETSOCKOPT_ERROR);
	if ((setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) == -1)
		error_output_and_exit(SETSOCKOPT_ERROR);
	ping.socket_fd = socket_fd;
}


unsigned short	checksum(void *address, int len)
{
	unsigned short	*buff;
	unsigned long	sum;

	buff = (unsigned short *)address;
	sum = 0;
	while (len > 1)
	{
		sum += *buff;
		buff++;
		len -= sizeof(unsigned short);
	}
	if (len)
		sum += *(unsigned char *)buff;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	return ((unsigned short)~sum);
}

char			send_packet(t_packet *packet)
{
	ssize_t sent_bytes;

	sent_bytes = sendto(ping.socket_fd, packet, sizeof(*packet), 0,
			(struct sockaddr*)&ping.sockaddr, sizeof(ping.sockaddr));
	if (sent_bytes <= 0)
	{
		if (errno == ENETUNREACH)
			error_output(NO_CONNEXION_ERROR);
		else
			error_output(SENDTO_ERROR);
		return (ERROR_CODE);
	}
	return (SUCCESS_CODE);
}

void			initialise_packet(struct s_packet *packet, struct timeval current_time)
{
	ft_bzero(packet, sizeof(t_packet));
	packet->icmp_header.icmp_type = ICMP_ECHO;
	packet->icmp_header.icmp_code = 0;
	packet->icmp_header.icmp_seq = BSWAP16(ping.seq);
	packet->icmp_header.icmp_id = BSWAP16(ping.process_id);
	ft_memcpy(&packet->icmp_header.icmp_dun, &(current_time.tv_sec), sizeof(current_time.tv_sec));
	packet->icmp_header.icmp_cksum = checksum(packet, sizeof(*packet));
}


void			save_current_time(struct timeval *destination)
{
	if (gettimeofday(destination, NULL) == -1)
		error_output_and_exit(TIMEOFDAY_ERROR);
}

void init_reply(t_reply *reply)
{
	ft_bzero(reply, sizeof(t_reply));
	reply->iov.iov_base = reply->receive_buffer;
	reply->iov.iov_len = sizeof(reply->receive_buffer);
	reply->msghdr.msg_name = ping.address;
	reply->msghdr.msg_iov = &reply->iov;
	reply->msghdr.msg_iovlen = 1;
	reply->msghdr.msg_control = &reply->control;
	reply->msghdr.msg_controllen = sizeof(reply->control);
}


char			check_reply(t_reply *reply)
{
	struct ip	*packet_content;

	packet_content = (struct ip *)reply->receive_buffer;
	if (packet_content->ip_p != IPPROTO_ICMP)
	{
	//	if (ping.flags & V_FLAG)
	//		error_output(REPLY_ERROR);
		return (ERROR_CODE);
	}
	reply->icmp = (struct icmp *)(reply->receive_buffer + (packet_content->ip_hl << 2));
	if (reply->icmp->icmp_type == 11 && reply->icmp->icmp_code == 0)
	{
		return (TTL_EXCEEDED_CODE);
	}
	else if (BSWAP16(reply->icmp->icmp_id) != ping.process_id || BSWAP16(reply->icmp->icmp_seq) != ping.seq)
	{
		init_reply(reply);
		return (receive_reply(reply));
	}
	return (SUCCESS_CODE);
}

char	receive_reply(t_reply *reply)
{
	reply->received_bytes = recvmsg(ping.socket_fd, &(reply->msghdr), 0);
	if (reply->received_bytes > 0)
	{
		return (check_reply(reply));
	}
	else
	{
		if ((errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
		{
			;
		}
		else
			error_output(RECV_ERROR);
		return (ERROR_CODE);
	}
	return (SUCCESS_CODE);
}

double			calculate_elapsed_time(struct timeval start, struct timeval end)
{
	return (((double)((double)end.tv_sec - (double)start.tv_sec) * 1000) +
		(double)((double)end.tv_usec - (double)start.tv_usec) / 1000);
}

void	display_sequence(int received_bytes, t_reply reply, struct timeval start_timestamp, struct timeval end_timestamp)
{
	short		reply_ttl;
	double		time_elapsed;
	struct ip	*packet_content;

	packet_content = (struct ip *)reply.receive_buffer;
	reply_ttl = (short)packet_content->ip_ttl;
	time_elapsed = calculate_elapsed_time(start_timestamp, end_timestamp);
	if (!(ping.flags))
	{
		if (ft_strcmp(ping.address, ping.user_requested_address))
		{
			printf("%lu bytes from %s (%s): icmp_seq=%d ttl=%d time=%.3lf ms\n", received_bytes - sizeof(struct ip),
				ping.reversed_address, ping.address, ping.seq, reply_ttl, time_elapsed);
		}
		else
		{
			printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%.3lf ms\n", received_bytes - sizeof(struct ip),
				ping.address, ping.seq, reply_ttl, time_elapsed);
		}
		set_rtt_stats(time_elapsed);
	}
}

void			wait_interval(struct timeval start)
{
	struct timeval	current_time;
	struct timeval	goal_time;

	if (ping.interval)
	{
		current_time = start;
		goal_time.tv_sec = current_time.tv_sec + (long)ping.interval;
		goal_time.tv_usec = current_time.tv_usec + (long)((ping.interval - (long)ping.interval) * 1000000);
		while (timercmp(&current_time, &goal_time, <))
		{
			save_current_time(&current_time);
		}
	}
}

void			packet_loop(void)
{
	t_packet			packet;
	struct timeval		current_start_timestamp;
	struct timeval		current_ending_timestamp;
	t_reply				reply;
	char				check;

	printf("PING %s (%s) 56(84) bytes of data.\n", ping.reversed_address, ping.address);
	ping.start = get_time();
	save_current_time(&ping.starting_time);
	while(ping.quit == 0)
	{
		save_current_time(&current_start_timestamp);
		initialise_packet(&packet, current_start_timestamp);
		ping.sent_packets++;
		check = send_packet(&packet);
		if (check == SUCCESS_CODE)
		{
			init_reply(&reply);
			check = receive_reply(&reply);
			if (check == SUCCESS_CODE)
			{
				ping.received_packets++;
				save_current_time(&current_ending_timestamp);
				display_sequence(reply.received_bytes, reply, current_start_timestamp, current_ending_timestamp);;
			}
			else if (check == TTL_EXCEEDED_CODE)
			{
		//		display_exceeded_sequence(reply);
		//		ping.error_packets++;
			}
		}
		ping.seq++;
		wait_interval(current_start_timestamp);
	}
}

int parsing(int ac, char **av)
{
	return 1;
}

int		main(int ac, char **av)
{
	if (parsing(ac, av))
	{
		init(av);
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, &sig_handler);
		if (ping.address)
			create_socket();
		if (ping.socket_fd != -1)
			packet_loop();
	}
	return (0);
}
