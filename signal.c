/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 20:09:38 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/13 12:05:54 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

extern int quit;

void sig_int()
{
    quit = 1;
    //print_stats();
}

void sig_quit()
{
     quit = 1;
}

void set_signal()
{
    signal(SIGINT, &sig_int);
    signal(SIGQUIT, &sig_quit);
}
