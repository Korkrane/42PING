/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:10:30 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/27 19:14:48 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"
#include <strings.h>

t_main *g_main;

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

void get_stats()
{
	//calcul every stats needed in g_main to display them after :)
}

void print_stats()
{
	get_stats();
	printf("\n--- %s ping statistics ---\n", g_main->host_name);
	printf("%d packets transmitted, %d received, %d%% packet loss, time %dms\n", 0, 0, 0, 0);
	printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", 0.0, 0.0, 0.0, 0.0);
}

void sig_int(int code)
{
	g_main->quit = 1;
	print_stats();
}

void sig_alrm(int code)
{
	g_main->quit = 1;
}

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	i = 0;
	dest = str;
	while (i < n)
	{
		dest[i] = c;
		i++;
	}
	return (dest);
}

void	ft_bzero(void *str, size_t n)
{
	ft_memset(str, 0, n);
}

int				get_addrinfo(char *av)
{
	struct addrinfo hints;
	struct addrinfo *res;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_flags = AI_CANONNAME;
	if (getaddrinfo(av, NULL, &hints, &res) != 0)
		return (1);
	g_main->host_name = res->ai_canonname;
	g_main->addr = (struct sockaddr_in *)res->ai_addr;
	return (0);
}

void	init(char **av)
{
	g_main = malloc(sizeof(t_main));
	bzero(g_main, sizeof(t_main));
	g_main->quit = 0;
	g_main->host_name = av[1];
	if (get_addrinfo(av[1]))
		printf("ft_ping: %s : ", g_main->host_name);
	g_main->host_addr = malloc(sizeof(char) * INET_ADDRSTRLEN);
	inet_ntop(AF_INET, (void *)&g_main->addr->sin_addr,
			g_main->host_addr, INET_ADDRSTRLEN);
}

int	parsing(int ac, char **av)
{
	if (ac < 2)
		return (0);
	for (int i = 1; i < ac; i++)
	{
		if(av[i][0] == '-')
		{
			if(av[i][1] == 'h')
				return(help());
			if(av[i][1] == 'v')
				g_main->opt = 1;
		}
		else
			return (1);
	}
	return (1);
}


unsigned short ft_check(void *b, int len)
{
	unsigned short *buf = b;
	unsigned int sum = 0;
	unsigned short res;

	for(sum = 0; len > 1; len -= 2)
		sum += *buf++;
	if(len == 1)
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	res = ~sum;
	return res;
}

void ping_loop(void)
{
	printf("PING %s (%s) 56(84) bytes of data.\n", g_main->host_name, g_main->host_addr);
	while(g_main->quit == 0)
	{
		int flag =1;
		bzero(&g_main->packet.msg, sizeof(g_main->packet.msg));	
		g_main->packet.ip = malloc(sizeof(struct iphdr));
		g_main->packet.ip->version = 4;
		//g_main->packet.ip->ihl = 4;
		g_main->packet.ip->ttl = 255;
		g_main->packet.ip->protocol = IPPROTO_ICMP;
		inet_pton(AF_INET, g_main->host_name ,&g_main->packet.ip->daddr);
		g_main->packet.ip->check = ft_check(&g_main->packet, sizeof(g_main->packet));
		g_main->packet.hdr = malloc(sizeof(struct icmphdr));
		for(int i = 0; i < sizeof(g_main->packet.msg)-1; i++)
				g_main->packet.msg[i] = i+'0';
		g_main->packet.hdr->type = ICMP_ECHO;
		g_main->packet.hdr->code = 0;
		g_main->packet.hdr->un.echo.id = getpid();
		g_main->packet.hdr->checksum = ft_check(&g_main->packet, sizeof(g_main->packet));
	//	sendto(g_main->sock_fd, (void *)g_main->packet, 64-sizeof(struct icmphdr), 0, (void *)g_main->addr);
	}
}

void create_socket()
{	
	int sock_fd;
	int ttl_val = 64;

	//sock_fd = socket(AF_INET, SOCK_RAW, 0);
	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_fd < 0)
		printf("error[%d] socket fd : %d creation\n",errno, sock_fd);
	setsockopt(sock_fd, IPPROTO_ICMP, IP_TTL, &ttl_val, sizeof(ttl_val));
	g_main->sock_fd = sock_fd;
}

int main(int ac, char **av)
{
	if	(parsing(ac, av))
	{
		init(av);
		if(get_addrinfo(av[1]))
		{
			printf("ft_ping: %s: Name or service not known\n", av[1]);
			return (1);
		}	
		signal(SIGINT, &sig_int);
		signal(SIGQUIT, &sig_alrm);
		create_socket();
		ping_loop();

	}
	return (0);
}
