/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 15:49:53 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/28 16:51:19 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

void print_stats()
{
	//	get_stats();
	printf("\n--- %s ping statistics ---\n", params.host_name);
	printf("%d packets transmitted, %d received, %d%% packet loss, time %dms\n", 0, 0, 0, 0);
	printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", 0.0, 0.0, 0.0, 0.0);
}

void sig_int()
{
	params.quit = 1;
	print_stats();
}

void sig_quit()
{
	params.quit = 1;
}

void sig_handler(int code)
{
	if(code == SIGINT)
		sig_int();
	else if(code == SIGQUIT)
		sig_quit();
}

int parsing(int ac, char **av)
{
	return 1;

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
	params.host_name = res->ai_canonname;
	ft_memcpy(&params.sockaddr, res->ai_addr, sizeof(struct sockaddr_in));
	inet_ntop(AF_INET, &(params.sockaddr.sin_addr), address, INET_ADDRSTRLEN);
	params.host_addr = ft_strdup(address);
	printf("address: %s\n", params.host_addr);
	printf("reversed_address: %s\n", params.host_name);
}

void init(char **av)
{
	params.pid = getpid();	
	params.seq = 1;
	params.ttl = 64;
	params.socket_fd = 0;
	params.host_name = av[1];
	ft_getadress(av[1]);
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

void init_packet(t_packet *packet, struct timeval current_time)
{
	ft_bzero(packet, sizeof(t_packet));
	packet->icmp_header.icmp_type = ICMP_ECHO;
	packet->icmp_header.icmp_code = 0;
	packet->icmp_header.icmp_seq = BSWAP16(params.seq);
	packet->icmp_header.icmp_id = BSWAP16(params.pid);
	ft_memcpy(&packet->icmp_header.icmp_dun, &(current_time.tv_sec), sizeof(current_time.tv_sec));
	packet->icmp_header.icmp_cksum = checksum(packet, sizeof(*packet));
}

int send_packet(t_packet *packet)
{
	ssize_t sent_bytes;

	sent_bytes = sendto(params.socket_fd, packet, sizeof(*packet), 0,
		(struct sockaddr*)&params.sockaddr, sizeof(params.sockaddr));
	if (sent_bytes <= 0)
	{
		if (errno == ENETUNREACH)
			printf("error sendo to reach host\n");
		else
			printf("error sendo\n");
		return (1);
	}
	/*
	if (ping.flags & F_FLAG)
	{
		ft_putchar('.');
		fflush(stdout);
	}
	*/
	return (0);
}

void			save_current_time(struct timeval *destination)
{
	if (gettimeofday(destination, NULL) == -1)
	{
		printf("error gettimeofday\n");
		return ;
	}
}

void	ping_loop()
{
	t_packet packet;
	int check;
	struct timeval current_start_timestamp;

	printf("PING %s (%s) 56(84) bytes of data.\n", params.host_name, params.host_addr);
	while(params.quit == 0)
	{
		save_current_time(&current_start_timestamp);
		init_packet(&packet, current_start_timestamp);
		check = send_packet(&packet);
	}
}

void create_socket()
{
	int socket_fd;
	if ((socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		printf("socket error creation\n");
		return ;
	}
	if (setsockopt(socket_fd, IPPROTO_IP, IP_TTL, &params.ttl, sizeof(params.ttl)) < 0)
	{
		printf("socket error setttlopt\n");
		return ;
	}
	params.socket_fd = socket_fd;
	printf("sock_fd: %d\n", socket_fd);	
}

int main(int ac, char **av)
{
	if (parsing(ac, av))
	{
		init(av);
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, &sig_handler);
		create_socket();
		if(params.socket_fd > 0)
		{
			ping_loop();	
		}
	}
}
