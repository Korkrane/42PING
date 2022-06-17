/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 18:06:43 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/17 13:30:06 by marvin           ###   ########.fr       */
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
#include <netinet/in.h>		 //include icmphdr struct and ICMP_* var
#include "../libft/libft.h"

#define BSWAP16(x) ((__uint16_t)((((x) >> 8) & 0xff) | (((x)&0xff) << 8)))

/*
** ERROR MESSAGE DEFINES
*/

#define USAGE "Usage: ft_ping [-v verbose] [-h help] [-t ttl] [-c count] [-i interval] [-f flood] destination"
#define BAD_FLAG_ERROR "ft_ping: invalid option -- '%c'\n"
#define BAD_TTL_ERROR "ft_ping: can't set time to live: invalid argument"
#define BAD_COUNT_ERROR "ft_ping: bad number of packets to transmit"
#define BAD_INTERVAL_ERROR "ft_ping: bad timing interval"
#define PERMISSION_ERROR "ft_ping: socket: operation not permitted"
#define UNKNOWN_ADDR_ERROR "ft_ping: %s: failure in name resolution\n"
#define SOCKET_ERROR "ft_ping: socket: operation not permitted"
#define SETSOCKOPT_ERROR "ft_ping: setsockopt: error while setting socket options"
#define TIMEOFDAY_ERROR "ft_ping: gettimeofday: error while trying to access current time"
#define SENDTO_ERROR "ft_ping: sendto: error while trying to send packet"
#define NO_CONNEXION_ERROR "ft_ping: sendto: the network is unreachable"
#define RECV_ERROR "ft_ping: recvmsg: error while trying to access ICMP reply"
#define REPLY_ERROR "ft_ping: reply is not what was expected (not ICMP)"
#define TIMEOUT_ERROR "ft_ping: recvmsg: request timed out"

#define ADDRINFO_ERROR(name) ("##name")
#define ERROR_I_OPT "ping: bad timing interval."
#define ERROR_C_OPT "ping: bad number of packets to transmit."
#define ERROR_L_OPT "ping: bad preload value, should be 1.65536"
#define ERROR_W_OPT "ping: bad wait time."					 // only if negative and numeric, if letter there is no error tho
#define ERROR_NEG_S_OPT "ping: illegal negative packet size" //-s letters = 0 by default return 8 bytes
#define ERROR_MAX_S_OPT "Error: packet size %d is too large. Maximum is 65507"
// idée : # define ERROR_MAX_S_OPT ("Error: packet size %d is too large. Maximum is 65507", packet_size)
// si -s lettre set size packet a 0

/*
** FUNCTION RETURN DEFINES
*/

#define TTL_EXCEEDED_CODE 2
#define ERROR_CODE 1
#define SUCCESS_CODE 0

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
	struct icmp icmp_header;
	char data_buffer[36]; // change for -s
} t_packet;

typedef struct s_time
{
	double avg;
	double min;
	double max;
	double total;
} t_time;

typedef struct s_opt
{
	int count;
	int interval;
	int preload;
	int ttl;
	double deadline;
	int packet_size;
	char *bell;
} t_opts;

typedef struct s_params
{
	char *user_requested_address;
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
int receive_reply(t_reply *reply);

void init_packet(struct s_packet *packet, struct timeval current_time);
void init_reply(t_reply *reply);
void init();

void set_signal();

void ft_getadress(char *host_name);
unsigned short checksum(void *address, int len);
void sig_int();
void sig_quit();

void add_no_params_opt(char opt);
void add_params_opt(char **av, int *k, int j, int *flag);
void get_count(char **av, int *i, int j);
void get_interval(char **av, int *i, int j);
void get_preload(char **av, int *i, int j);
void get_ttl(char **av, int *i, int j);
void get_deadline(char **av, int *i, int j);
void get_packetsize(char **av, int *i, int j);

double get_time(void);
double get_elapsed_time(double starter);
double calculate_elapsed_time(struct timeval start, struct timeval end);
void set_time(struct timeval *destination);

void add_options_modification();
int print_stats();
void set_rtt_stats(double rtt);
double get_mdev();

void create_socket(void);

int send_packet(t_packet *packet);

void _checkOpt(); // TO DELETE
#endif
