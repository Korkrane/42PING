/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 20:09:38 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/28 20:11:31 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

void sig_int()
{
	params.quit = 1;
	print_stats();
}

void sig_quit()
{
	params.quit = 1;
}

void set_signal()
{
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
}
