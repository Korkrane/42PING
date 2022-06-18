/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 22:23:15 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/18 04:12:21 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

int sendPacket(t_packet *packet)
{
    params.sent_packets++;
    if (sendto(params.socket_fd, packet, sizeof(*packet), 0,(struct sockaddr *)&params.sockaddr, sizeof(params.sockaddr)) <= 0)
    {
        if (errno == ENETUNREACH)
            ft_printerr(NO_CONNEXION_ERROR);
        else
            ft_printerr(SENDTO_ERROR);
        return (false);
    }
    return (true);
}

static unsigned short checksum(void *address, int len)
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

void initPacket(struct s_packet *packet)
{
    ft_bzero(packet, sizeof(t_packet));
    packet->hdr.type = ICMP_ECHO;
    packet->hdr.un.echo.id = BSWAP16(params.process_id);
    packet->hdr.un.echo.sequence = BSWAP16(params.seq);

    for (int i = 0; i < (int)(sizeof(packet->msg) - 1); i++)
        packet->msg[i] = i + '0';
    packet->msg[i] = 0;

    packet->hdr.checksum = checksum(packet, sizeof(*packet));
}
