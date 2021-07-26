/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:10:30 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/26 23:19:41 by bahaas           ###   ########.fr       */
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

void ping_loop(void)
{
	printf("PING %s (%s) 56(84) bytes of data.\n", g_main->host_name, g_main->host_addr);
	while(g_main->quit == 0)
		;
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
		ping_loop();

	}
	return (0);
}
