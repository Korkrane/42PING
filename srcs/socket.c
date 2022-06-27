/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 22:20:43 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/24 16:50:34 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

void addTTLoptionsTo(int socket)
{
	if ((setsockopt(socket, IPPROTO_IP, IP_TTL, &(params.ttl), sizeof(params.ttl))) == -1)
		printErrorAndExit(SETSOCKOPT_ERROR, 1);
}

void addTimeoptionTo(int socket)
{
	struct timeval timeout;

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	if ((setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) == -1)
		printErrorAndExit(SETSOCKOPT_ERROR, 1);
}

int createSocket()
{
	int newSocket;

	if ((newSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
		printErrorAndExit(SOCKET_ERROR, 1);
	return newSocket;
}
