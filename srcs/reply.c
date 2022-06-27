/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 22:25:00 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/24 16:58:21 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

static int checkReply(t_reply *reply)
{
	struct ip *packet_content;

	packet_content = (struct ip *)reply->receive_buffer;
	if (packet_content->ip_p != IPPROTO_ICMP)
	{
		//	if (params.flags & V_FLAG)
		//		printError(REPLY_ERROR);
		return (false);
	}
	reply->icmp = (struct icmp *)(reply->receive_buffer + (packet_content->ip_hl << 2));
	if (reply->icmp->icmp_type == 11 && reply->icmp->icmp_code == 0)
		return (TTL_EXCEEDED_CODE);
	else if (BSWAP16(reply->icmp->icmp_id) != params.process_id || BSWAP16(reply->icmp->icmp_seq) != params.seq)
	{
		initReply(reply);
		return (recvReply(reply));
	}
	return (true);
}

int recvReply(t_reply *reply)
{
	reply->received_bytes = recvmsg(params.socket_fd, &(reply->msghdr), 0);
	if (reply->received_bytes > 0)
		return (checkReply(reply));
	else
	{
		if ((errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
		{
			printf("errror\n");
			;
		}
		else
			printError(RECV_ERROR);
		return (false);
	}
	return (true);
}

void initReply(t_reply *reply)
{
	ft_bzero(reply, sizeof(t_reply));
	reply->iov.iov_base = reply->receive_buffer;
	reply->iov.iov_len = sizeof(reply->receive_buffer);
	reply->msghdr.msg_name = params.address;
	// reply->msghdr.msg_namelen = ft_strlen(params.address);
	reply->msghdr.msg_iov = &reply->iov;
	reply->msghdr.msg_iovlen = 1;
	reply->msghdr.msg_control = &reply->control;
	reply->msghdr.msg_controllen = sizeof(reply->control);
}
