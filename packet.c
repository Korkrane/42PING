/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 22:23:15 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/13 12:17:07 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

int send_packet(t_packet *packet, t_params *params)
{
    ssize_t sent_bytes;

    sent_bytes = sendto(params->socket_fd, packet, sizeof(*packet), 0,
                        (struct sockaddr *)&params->sockaddr, sizeof(params->sockaddr));
    if (sent_bytes <= 0)
    {
        if (errno == ENETUNREACH)
            error_output(NO_CONNEXION_ERROR);
        else
            error_output(SENDTO_ERROR);
        return (false);
    }
    if (params->flags & f)
        printf(".");
    return (true);
}

unsigned short checksum(void *address, int len)
{
    unsigned short *buff;
    unsigned long sum;

    buff = (unsigned short *)address;
    sum = 0;
    while (len > 1)
    {
        sum += *buff;
        buff++;
        len -= sizeof(unsigned short);
    }
    if (len)
        sum += *(unsigned char *)buff;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return ((unsigned short)~sum);
}

void init_packet(struct s_packet *packet, struct timeval current_time, t_params *params)
{
    ft_bzero(packet, sizeof(t_packet));
    packet->icmp_header.icmp_type = ICMP_ECHO;
    packet->icmp_header.icmp_code = 0;
    packet->icmp_header.icmp_seq = BSWAP16(params->seq);
    packet->icmp_header.icmp_id = BSWAP16(params->process_id);
    ft_memcpy(&packet->icmp_header.icmp_dun, &(current_time.tv_sec), sizeof(current_time.tv_sec));
    packet->icmp_header.icmp_cksum = 0;
    packet->icmp_header.icmp_cksum = checksum(packet, sizeof(*packet));
    // handle packet error here :)
    // printf("sizeof(*packet): %ld\n", sizeof(*packet));
    params->sent_packets++;
}
