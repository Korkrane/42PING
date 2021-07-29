/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 18:06:43 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/29 18:51:48 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
#define FT_PING_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <errno.h>
#include <math.h>

#include <netinet/ip_icmp.h> //include icmphdr struct and ICMP_* var
#include <netinet/in.h> //include icmphdr struct and ICMP_* var
#include "../libft/libft.h"

# define BSWAP16(x)			((__uint16_t) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)))

/*
** ERROR MESSAGE DEFINES
*/

# define USAGE				"Usage: ft_ping [-v verbose] [-h help] [-t ttl] [-c count] [-i interval] [-f flood] destination"
# define BAD_FLAG_ERROR		"ft_ping: invalid option -- '%c'\n"
# define BAD_TTL_ERROR		"ft_ping: can't set time to live: invalid argument"
# define BAD_COUNT_ERROR	"ft_ping: bad number of packets to transmit"
# define BAD_INTERVAL_ERROR	"ft_ping: bad timing interval"
# define PERMISSION_ERROR	"ft_ping: socket: operation not permitted"
# define UNKNOWN_ADDR_ERROR	"ft_ping: %s: failure in name resolution\n"
# define SOCKET_ERROR		"ft_ping: socket: operation not permitted"
# define SETSOCKOPT_ERROR	"ft_ping: setsockopt: error while setting socket options"
# define TIMEOFDAY_ERROR	"ft_ping: gettimeofday: error while trying to access current time"
# define SENDTO_ERROR		"ft_ping: sendto: error while trying to send packet"
# define NO_CONNEXION_ERROR	"ft_ping: sendto: the network is unreachable"
# define RECV_ERROR			"ft_ping: recvmsg: error while trying to access ICMP reply"
# define REPLY_ERROR		"ft_ping: reply is not what was expected (not ICMP)"
# define TIMEOUT_ERROR		"ft_ping: recvmsg: request timed out"

/*
** FUNCTION RETURN DEFINES
*/

# define TTL_EXCEEDED_CODE	2
# define ERROR_CODE			1
# define SUCCESS_CODE		0

typedef enum e_flags
{
	V = 1 << 0,
	D = 1 << 1,
	I = 1 << 2,
	N = 1 << 4,
	H = 1 << 5,
	F = 1 << 6,
	L = 1 << 7,
	T = 1 << 8,
	A = 1 << 9,
	W = 1 << 10,
	Q = 1 << 11,
	S = 1 << 12
}				t_flags;

typedef struct				s_reply
{
	int						received_bytes;
	struct msghdr			msghdr;
	struct iovec			iov;
	struct icmp				*icmp;
	char					receive_buffer[84];
	char					control[CMSG_SPACE(sizeof(int))];
}							t_reply;

typedef struct				s_packet
{
	struct icmp				icmp_header;
	char					data_buffer[36];
}							t_packet;

typedef struct				s_time
{
	double avg;
	double min;
	double max;
	double total;
}							t_time;

typedef struct				s_opt
{
	int count;
	int interval;
	int preload;
	int ttl;
	double deadline;
	int		packet_size;
}							t_opts;

typedef struct s_params
{
	int						quit;
	int						flags;
	t_opts					opts;
	double					interval;
	char					*user_requested_address;
	char					*address;
	char					*reversed_address;
	int						ttl;
	pid_t					process_id;
	int						socket_fd;
	int						sent_packets;
	int						received_packets;
	int						error_packets;
	int						seq;
	struct sockaddr_in		sockaddr;
	struct timeval			starting_time;
	struct timeval			ending_time;
	long					start;
	long					end;
	int						packet_size;
	t_time					time;

}				t_params;


t_params params;
char	receive_reply(t_reply *reply);


void			init_packet(struct s_packet *packet, struct timeval current_time);
void init_reply(t_reply *reply);
void	init(int ac, char **av);

void set_signal();
void print_stats();

void ft_getadress(char *host_name);
unsigned short	checksum(void *address, int len);
void sig_int();
void sig_quit();
#endif
