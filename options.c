/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 18:57:14 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/17 17:28:08 by bahaas           ###   ########.fr       */
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

void add_params_opt(char **av, int *i, int j, int *flag)
{
	switch(av[*i][j])
	{
		case 'c': params.flags |= c; params.opts.count = get_count(av, i, j, 1, LLONG_MAX); *flag = 0; break; //count limit packet to send
		// case 'i': params.flags |= i; get_interval(av, i, j, INT_MAX / 1000); *flag = 0; break; //set new interval
		// case 'l': params.flags |= l; get_preload(av, i, j); *flag = 0; break; //set preload packet to send
		// case 't': params.flags |= t; get_ttl(av, i, j, UCHAR_MAX); *flag = 0; break; //set new ttl
		// case 's': params.flags |= s; get_packetsize(av, i, j, 127992, USHRT_MAX + 1); *flag = 0; break; //set new packet size
		//case 'w': params.flags |= w; get_deadline(av, i, j, INT_MAX); *flag = 0; break; //set global deadline
	}
}

void printerr_limits(long long min, long long max, long long val)
{
	if(max == LLONG_MAX && val > 0)
		printf("ft_ping: invalid argument: '%lld': Numerical result out of range\n", val);
	else
	printf("ft_ping: invalid argument: '%lld': out of range: %lld <= value <= %lld\n", val, min, max);
	exit(1);
}

long long	get_count(char **av, int *i, int j, long long min_limit, long long max_limit)
{
	int	count;

	if (av[*i][j + 1] == '\0' && av[*i + 1] != NULL)
	{
		long long nbr = 0;
		if (ft_strcmp(av[*i + 1], "9223372036854775808") == 0)
			nbr = atoll(av[*i + 1]) + 1;
		else
			nbr = atoll(av[*i + 1]);
		if(!ft_is_nbr(av[*i + 1]))
			ft_printerr_exit(ft_strjoin("ft_ping: invalid argument: ", av[*i + 1]), 1);
		++*i;
		if (nbr < min_limit || nbr > max_limit)
			printerr_limits(min_limit, max_limit, nbr);
		return nbr;
	}
	else if (ft_isdigit(av[*i][j + 1]) || av[*i][j + 1] == '-')
	{
		printf("lal\n");
		if (!ft_is_nbr(&av[*i][j + 1]))
			ft_printerr_exit(ft_strjoin("ft_ping: invalid argument: ", &av[*i][j + 1]), 1);
		long long nbr = 0;
		if(ft_strcmp(&av[*i][j + 1], "9223372036854775808")==0)
			nbr = atoll(&av[*i][j + 1]) + 1;
		else
			nbr = atoll(&av[*i][j + 1]);
		if (nbr < min_limit || nbr > max_limit)
			printerr_limits(min_limit, max_limit, nbr);
		return nbr;
	}
	return 0;
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
