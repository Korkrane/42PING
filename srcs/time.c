/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:00:52 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/24 17:29:06 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

/**
 * @brief Get the Time
 *
 * @return double
 */
double getTime()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

/**
 * @brief Get the Elapsed Time
 *
 * @param starter
 * @return double
 */
double getElapsedTime(double starter) //TODO delete and swap with getTimeDelta
{
	struct timeval tv;
	double end;

	gettimeofday(&tv, NULL);
	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (end - starter);
}

/**
 * @brief Get the Time Diff
 *
 * @param start the smallest timeval
 * @param end the biggest timeval
 * @return time passed between each time value
 */

double getTimeDiff(struct timeval start, struct timeval end)
{
	return (((double)((double)end.tv_sec - (double)start.tv_sec) * 1000) +
			(double)((double)end.tv_usec - (double)start.tv_usec) / 1000);
}

void setTime(struct timeval *time)
{
	if (gettimeofday(time, NULL) == -1)
		printErrorAndExit(TIMEOFDAY_ERROR, 1);
}

void waitForInterval(struct timeval start)
{
    struct timeval interval;

    if (params.interval)
    {
        interval.tv_sec = start.tv_sec + (long)params.interval;
        interval.tv_usec = start.tv_usec + (long)((params.interval - (long)params.interval) * 1000000);
        while (timercmp(&start, &interval, <))
            setTime(&start);
    }
}
