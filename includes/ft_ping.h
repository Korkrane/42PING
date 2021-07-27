/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 18:06:43 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/27 18:41:03 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
#define FT_PING_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <errno.h>

#include <netinet/ip_icmp.h> //include icmphdr struct and ICMP_* var
#include <netinet/in.h> //include icmphdr struct and ICMP_* var
#include "../libft/libft.h"

typedef struct s_pckt
{
	struct icmphdr *hdr;
	struct iphdr *ip;
	char	msg[64-sizeof(struct icmphdr)];
}				t_pckt;

typedef struct s_main
{
	struct sockaddr_in	*addr;
	char				*host_name;
	char				*host_addr;
	t_pckt				packet;
	int sock_fd;
	int opt;
	int quit;
	int send_count;
	int receive_count;
}				t_main;

extern t_main *g_main;


void sig_int(int code);
void sig_alrm(int code);
#endif
