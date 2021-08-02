/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 22:20:43 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/31 01:49:54 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

extern char *program_invocation_short_name;

void	create_socket(void)
{
	int				socket_fd;
	struct timeval	timeout;

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	//if ((socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
	if ((socket_fd = socket(AF_INET, 645, IPPROTO_ICMP)) == -1)
	{
		printf("errno : %d\n", errno);
		printf("%s\n", strerror(errno));
		perror("ft_ping: socket");
		perror(program_invocation_short_name);
		printf("\n");
		//perror(program_invocation_name_short);
	}
	if ((setsockopt(socket_fd, IPPROTO_IP, IP_TTL, &(params.ttl), sizeof(params.ttl))) == -1)
		error_output_and_exit(SETSOCKOPT_ERROR);
	if ((setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) == -1)
		error_output_and_exit(SETSOCKOPT_ERROR);
	params.socket_fd = socket_fd;
}
