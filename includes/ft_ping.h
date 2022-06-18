/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 18:06:43 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/18 02:34:53 by bahaas           ###   ########.fr       */
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
#include <stdbool.h>
#include <netinet/ip_icmp.h>
#include "../libft/libft.h"

#define BAD_TTL_ERROR "ft_ping: can't set time to live: invalid argument"
#define BAD_COUNT_ERROR "ft_ping: bad number of packets to transmit"
#define BAD_INTERVAL_ERROR "ft_ping: bad timing interval"
#define PERMISSION_ERROR "ft_ping: socket: operation not permitted"
#define SOCKET_ERROR "ft_ping: socket: operation not permitted"
#define SETSOCKOPT_ERROR "ft_ping: setsockopt: error while setting socket options"
#define TIMEOFDAY_ERROR "ft_ping: gettimeofday: error while trying to access current time"
#define SENDTO_ERROR "ft_ping: sendto: error while trying to send packet"
#define NO_CONNEXION_ERROR "ft_ping: sendto: the network is unreachable"
#define RECV_ERROR "ft_ping: recvmsg: error while trying to access ICMP reply"
#define REPLY_ERROR "ft_ping: reply is not what was expected (not ICMP)"
#define TIMEOUT_ERROR "ft_ping: recvmsg: request timed out"

#define ERROR_I_OPT "ping: bad timing interval."
#define ERROR_C_OPT "ping: bad number of packets to transmit."
#define ERROR_L_OPT "ping: bad preload value, should be 1.65536"
#define ERROR_W_OPT "ping: bad wait time."					 // only if negative and numeric, if letter there is no error tho
#define ERROR_NEG_S_OPT "ping: illegal negative packet size" //-s letters = 0 by default return 8 bytes
#define ERROR_MAX_S_OPT "Error: packet size %d is too large. Maximum is 65507"
// idée : # define ERROR_MAX_S_OPT ("Error: packet size %d is too large. Maximum is 65507", packet_size)
// si -s lettre set size packet a 0

#define BSWAP16(x) ((__uint16_t)((((x) >> 8) & 0xff) | (((x)&0xff) << 8)))
#define TTL_EXCEEDED_CODE 2
#define PACKET_SIZE 64

typedef enum e_flags
{
	v = 1 << 0,
	D = 1 << 1,
	i = 1 << 2,
	n = 1 << 3,
	H = 1 << 4,
	f = 1 << 5,
	l = 1 << 6,
	t = 1 << 7,
	a = 1 << 8,
	w = 1 << 9,
	q = 1 << 10,
	s = 1 << 11,
	c = 1 << 12
} t_flags;

typedef struct s_reply
{
	int received_bytes;
	struct msghdr msghdr;
	struct iovec iov;
	struct icmp *icmp;
	char receive_buffer[84]; // change for -s
	char control[CMSG_SPACE(sizeof(int))];
} t_reply;



typedef struct s_packet
{
	struct icmphdr hdr;
	char msg[PACKET_SIZE - sizeof(struct icmphdr)];
} t_packet;

typedef struct s_time
{
	double avg;
	double min;
	double max;
	double total;
	double total2;
} t_time;

typedef struct s_opt
{
	int count;
	int interval;
	int preload;
	int ttl;
	double deadline;
	int packet_size;
} t_opts;

typedef struct s_params
{
	char *requestedAddress;
	char *address;
	char *reversed_address;
	int quit;
	int flags;
	double interval;
	int ttl;
	pid_t process_id;
	int socket_fd;
	int sent_packets;
	int received_packets;
	int error_packets;
	int seq;
	struct sockaddr_in sockaddr;
	double start;
	double end;
	int packet_size;
	t_opts opts;
	t_time time;
	t_reply reply;
} t_params;

t_params params;

/** to delete later **/
void 	checkOptDebug();

/** options.c **/
void	addParamWithoutValue(char opt);
void	addParamWithValue(char **av, int *k, int j, int *flag);

/** init.c **/
void	init();
void	addOptionsModifications();

/** socket.c **/
void	createSocket();

/** reply.c **/
void	initReply(t_reply *reply);
int		recvReply(t_reply *reply);

/** signal.c **/
void	initSignal();

/** time.c **/
double	getTime();
double	getElapsedTime(double starter);
double	getTimeDiff(struct timeval start, struct timeval end);
void	setTime(struct timeval *destination);
void	waitForInterval(struct timeval start);

/** packet.c **/
void	initPacket(struct s_packet *packet);
int		sendPacket(t_packet *packet);

/** stats.c **/
void	setRTTstats(double rtt);
double	getMdev();

/** utils.c **/

int		hasOptionEnabled(int opt);
int		hasReachedCountLimit();

/** print.c **/

void	printTimestamp();
void	printPingInfo();
void	printReplyInfos(t_reply reply, double time);
void	printStats();

#endif