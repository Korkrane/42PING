/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 22:25:00 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/30 14:54:00 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

int			check_reply(t_reply *reply)
{
	struct ip	*packet_content;

	packet_content = (struct ip *)reply->receive_buffer;
	if (packet_content->ip_p != IPPROTO_ICMP)
	{
		//	if (params.flags & V_FLAG)
		//		error_output(REPLY_ERROR);
		return (false);
	}
	reply->icmp = (struct icmp *)(reply->receive_buffer + (packet_content->ip_hl << 2));
	if (reply->icmp->icmp_type == 11 && reply->icmp->icmp_code == 0)
		return (TTL_EXCEEDED_CODE);
	else if (BSWAP16(reply->icmp->icmp_id) != params.process_id || BSWAP16(reply->icmp->icmp_seq) != params.seq)
	{
		init_reply(reply);
		return (receive_reply(reply));
	}
	return (true);
}

int	receive_reply(t_reply *reply)
{
	reply->received_bytes = recvmsg(params.socket_fd, &(reply->msghdr), 0);
	if (reply->received_bytes > 0)
		return (check_reply(reply));
	else
	{
		if ((errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
		{
			;
		}
		else
			error_output(RECV_ERROR);
		return (false);
	}
	return (true);
}

void init_reply(t_reply *reply)
{
	ft_bzero(reply, sizeof(t_reply));
	reply->iov.iov_base = reply->receive_buffer;
	reply->iov.iov_len = sizeof(reply->receive_buffer);
	reply->msghdr.msg_name = params.address;
	//reply->msghdr.msg_namelen = ft_strlen(params.address);
	reply->msghdr.msg_iov = &reply->iov;
	reply->msghdr.msg_iovlen = 1;
	reply->msghdr.msg_control = &reply->control;
	reply->msghdr.msg_controllen = sizeof(reply->control);
}
