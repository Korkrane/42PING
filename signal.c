/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 20:09:38 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/17 18:36:50 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

void sigInt()
{
	params.quit = 1;
	printStats();
}

void sigQuit()
{
	params.quit = 1;
}

void initSignal()
{
	signal(SIGINT, &sigInt);
	signal(SIGQUIT, &sigQuit);
}
