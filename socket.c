/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 22:20:43 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/13 11:50:04 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

void create_socket(t_params *params)
{
    int socket_fd;
    struct timeval timeout;

    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    // if ((socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
    //     error_output_and_exit(SOCKET_ERROR);
    // if ((setsockopt(socket_fd, IPPROTO_IP, IP_TTL, &(params->ttl), sizeof(params->ttl))) == -1)
    //     error_output_and_exit(SETSOCKOPT_ERROR);
    // if ((setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) == -1)
    //     error_output_and_exit(SETSOCKOPT_ERROR);
    // params->socket_fd = socket_fd;
}
