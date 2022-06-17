/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:00:52 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/17 12:23:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

double get_time(void)
{
	struct timeval tv;
	double end;

	gettimeofday(&tv, NULL);
	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (end);
}

double get_elapsed_time(double starter)
{
	struct timeval tv;
	double end;

	gettimeofday(&tv, NULL);
	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (end - starter);
}

double calculate_elapsed_time(struct timeval start, struct timeval end)
{
	return (((double)((double)end.tv_sec - (double)start.tv_sec) * 1000) +
			(double)((double)end.tv_usec - (double)start.tv_usec) / 1000);
}

void set_time(struct timeval *destination)
{
	if (gettimeofday(destination, NULL) == -1)
		ft_printerr_exit(TIMEOFDAY_ERROR, 1);
}
