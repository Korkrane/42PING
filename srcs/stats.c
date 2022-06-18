/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:05:15 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/18 04:12:48 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"


/**
 * @brief update the statistics value printed at the end
 *
 * @param rtt round-trip-time
 */
void setRTTstats(double rtt)
{
	if(params.time.min == 0 || rtt < params.time.min)
		params.time.min = rtt;
	if(params.time.max == 0 || rtt > params.time.max)
		params.time.max = rtt;
	params.time.total += rtt;
	params.time.avg = params.time.total / params.received_packets;
	params.time.total2 += rtt * rtt;
}

double getMdev()
{
	double mdev;
	double avg;
	double avg_square;

	avg = params.time.total / params.received_packets;
	avg_square = (params.time.total * params.time.total) / params.received_packets;
	mdev = sqrt(avg_square - (avg * avg));

    //tsum += triptime;
	//tsum2 += (long long)triptime * (long long)triptime
           // tsum /= nreceived + nrepeats;
            //tsum2 /= nreceived + nrepeats;
        //double newmdev = sqrt(params.time.total2 - 	params.time.total * 	params.time.total);


		// double n = nreceived + nrepeats;
		// double avg = tsum / n;
		// double vari = tsumsq / n - avg * avg;
		// (void)printf(
		//     "round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
		//     tmin, avg, tmax, sqrt(vari));

		double n =  params.received_packets;
		double avg2 = params.time.total / n;
		double vari = params.time.total2 / n - avg2 * avg2;
		double newmdev = sqrt(vari);
	printf("old mdev: %f\n", mdev);
	printf("new mdev: %f\n", newmdev);
	return (mdev);
}
