/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 22:20:43 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/18 04:12:44 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

void createSocket()
{
	int socketFd;
	struct timeval timeout;

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	if (!params.address)
		return;
	if ((socketFd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
		ft_printerr_exit(SOCKET_ERROR, 1);
	if ((setsockopt(socketFd, IPPROTO_IP, IP_TTL, &(params.ttl), sizeof(params.ttl))) == -1)
		ft_printerr_exit(SETSOCKOPT_ERROR, 1);
	if ((setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) == -1)
		ft_printerr_exit(SETSOCKOPT_ERROR, 1);
	params.socket_fd = socketFd;
}
