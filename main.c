/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:10:30 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/23 19:13:32 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_main *g_main;

static void print_help()
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
}

int use_help()
{
	print_help();
	return (0);
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
				return(use_help());
			if(av[i][1] == 'v')
				g_main->opt = 1;
		}
		else
			return (1);
	}
}

void get_stats()
{
	//calcul every stats needed in g_main to display them after :)
}

void print_stats()
{
	get_stats();
	printf("--- %s ping statistics ---\n", "TEST");
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

void	init()
{
	g_main = malloc(sizeof(t_main));
	g_main->quit = 0;
}

int main(int ac, char **av)
{
	if	(parsing(ac, av))
	{
		init();
		signal(SIGINT, &sig_int);
		signal(SIGQUIT, &sig_alrm);
		while(g_main->quit == 0)
			;
	}
	return (0);
}
