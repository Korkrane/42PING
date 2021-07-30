/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 18:57:14 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/30 15:16:25 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

void add_no_params_opt(char opt)
{
	switch(opt)
	{
		case 'v': params.flags |= v; break; //verbose mode
		case 'D': params.flags |= D; break; //timestamp on each line
		case 'n': params.flags |= n; break; //display only ip address (on each)
		case 'f': params.flags |= f; break; //flood (print . on send and \b on receive) + interval = 0 unless specified
		case 'a': params.flags |= a; break; //bell song on each line
		case 'q': params.flags |= q; break; //quiet ouput
	}
}

void add_params_opt(char **av, int *k, int j, int *flag)
{
	switch(av[*k][j])
	{
		case 'c': params.flags |= c; get_count(av, k, j); *flag = 0; break; //count limit packet to send 
		case 'i': params.flags |= i; get_interval(av, k, j); *flag = 0; break; //set new interval
		case 'l': params.flags |= l; get_preload(av, k, j); *flag = 0; break; //set preload packet to send
		case 't': params.flags |= t; get_ttl(av, k, j); *flag = 0; break; //set new ttl
		case 's': params.flags |= s; get_packetsize(av, k, j); *flag = 0; break; //set new packet size
		case 'w': params.flags |= w; get_deadline(av, k, j); *flag = 0; break; //set global deadline
	}
}

void	get_count(char **av, int *i, int j)
{
	int	count;

	if (av[*i][j + 1] == '\0' && av[*i + 1] != NULL)
	{
		params.opts.count = ft_atoi(av[*i + 1]);	
		++*i;
	}
	else if (ft_isdigit(av[*i][j + 1]))
	{
		params.opts.count = ft_atoi(&av[*i][j + 1]);
	}
	else
		printf("erro count -c opt\n");
}

void	get_interval(char **av, int *i, int j)
{
	int	count;

	if (av[*i][j + 1] == '\0' && av[*i + 1] != NULL)
	{
		params.opts.interval = ft_atoi(av[*i + 1]);
		++*i;
	}
	else if (ft_isdigit(av[*i][j + 1]))
	{
		params.opts.interval = ft_atoi(&av[*i][j + 1]);
		//++*j to check nexxt opt ?
	}
	else
		printf("erro interval -i opt\n");
}

void	get_preload(char **av, int *i, int j)
{
	int	count;

	if (av[*i][j + 1] == '\0' && av[*i + 1] != NULL)
	{
		params.opts.preload = ft_atoi(av[*i + 1]);
		++*i;
	}
	else if (ft_isdigit(av[*i][j + 1]))
	{
		params.opts.preload = ft_atoi(&av[*i][j + 1]);
		//++*j to check nexxt opt ?
	}
	else
		printf("erro preload -l opt\n");
}

void	get_deadline(char **av, int *i, int j)
{
	int	count;

	if (av[*i][j + 1] == '\0' && av[*i + 1] != NULL)
	{
		params.opts.deadline = ft_atoi(av[*i + 1]);
		++*i;
	}
	else if (ft_isdigit(av[*i][j + 1]))
	{
		params.opts.deadline = ft_atoi(&av[*i][j + 1]);
		//++*j to check nexxt opt ?
	}
	else
		printf("error deadline -w opt\n");
}

void	get_ttl(char **av, int *i, int j)
{
	int	count;

	if (av[*i][j + 1] == '\0' && av[*i + 1] != NULL)
	{
		params.opts.ttl = ft_atoi(av[*i + 1]);
		++*i;
	}
	else if (ft_isdigit(av[*i][j + 1]))
	{
		params.opts.ttl = ft_atoi(&av[*i][j + 1]);
		//++*j to check nexxt opt ?
	}
	else
		printf("error ttl -t opt\n");
}

void	get_packetsize(char **av, int *i, int j)
{
	int	count;

	if (av[*i][j + 1] == '\0' && av[*i + 1] != NULL)
	{
		params.opts.packet_size = ft_atoi(av[*i + 1]);
		++*i;
	}
	else if (ft_isdigit(av[*i][j + 1]))
	{
		params.opts.packet_size = ft_atoi(&av[*i][j + 1]);
		//++*j to check nexxt opt ?
	}
	else
		printf("error packetsize -s opt\n");
}

