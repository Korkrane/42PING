/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 18:57:14 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/29 18:59:53 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"


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

