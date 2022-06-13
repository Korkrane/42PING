/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:03:54 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/09 19:21:19 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

void add_no_params_opt(char opt, t_params params)
{
    switch (opt)
    {
    case 'v':
        params.flags |= v;
        break; // verbose mode
    case 'D':
        params.flags |= D;
        break; // timestamp on each line
    case 'n':
        params.flags |= n;
        break; // display only ip address (on each)
    case 'f':
        params.flags |= f;
        break; // flood (print . on send and \b on receive) + interval = 0 unless specified
    case 'a':
        params.flags |= a;
        break; // bell song on each line
    case 'q':
        params.flags |= q;
        break; // quiet ouput
    }
}
/*
void add_params_opt(char **av, int *k, int j, int *flag)
{
    switch (av[*k][j])
    {
    case 'c':
        params.flags |= c;
        get_count(av, k, j);
        *flag = 0;
        break; // count limit packet to send
    case 'i':
        params.flags |= i;
        get_interval(av, k, j);
        *flag = 0;
        break; // set new interval
    case 'l':
        params.flags |= l;
        get_preload(av, k, j);
        *flag = 0;
        break; // set preload packet to send
    case 't':
        params.flags |= t;
        get_ttl(av, k, j);
        *flag = 0;
        break; // set new ttl
    case 's':
        params.flags |= s;
        get_packetsize(av, k, j);
        *flag = 0;
        break; // set new packet size
    case 'w':
        params.flags |= w;
        get_deadline(av, k, j);
        *flag = 0;
        break; // set global deadline
    }
}
*/