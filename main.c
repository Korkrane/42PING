/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 16:53:09 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/17 13:59:19 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

int help()
{
    fprintf(stderr, "\nUsage\n  ping [options] <destination>\n"
                    "\nOptions:\n"
                    "  <destinaton>\t     dns name or ip address\n"
                    "  -h\t\t     print help and exit\n"
                    "  -v\t\t     verbose output\n");
    return 0;
}

void ft_getadress(char *host_name)
{
    struct addrinfo hints;
    struct addrinfo *res = NULL;
    char address[INET_ADDRSTRLEN];

    ft_bzero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;
    if (getaddrinfo(host_name, NULL, &hints, &res) != 0)
    {
        // printf("error in getaddress\n");
        // return;
        fprintf(stderr, "ping: %s: Name or service not known\n", host_name);
        exit(2);
    }
    params.reversed_address = res->ai_canonname;
    ft_memcpy(&params.sockaddr, res->ai_addr, sizeof(struct sockaddr_in));
    inet_ntop(AF_INET, &(params.sockaddr.sin_addr), address, INET_ADDRSTRLEN);
    params.address = ft_strdup(address);
}

void check_D_opt()
{
    if (params.flags & D)
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        printf("[%ld.%ld]", tv.tv_sec, tv.tv_usec);
    }
}

void display_sequence(t_reply reply, double time)
{
    short reply_ttl;
    struct ip *packet_content;

    // printf("reply bytes : %d\n", reply.received_bytes);
    packet_content = (struct ip *)reply.receive_buffer;
    reply_ttl = (short)packet_content->ip_ttl;
    if (!(params.flags & q))
    {
        check_D_opt();
        if (!(params.flags & f))
        {
            if (ft_strcmp(params.address, params.user_requested_address) && !(params.flags & n))
                printf("%lu bytes from %s (%s): icmp_seq=%d ttl=%d time=%.2lf ms%s\n", reply.received_bytes - sizeof(struct ip),
                       params.reversed_address, params.address, params.seq, reply_ttl, time, params.opts.bell);
            else if (params.flags & n) // bonus -n
                printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%.2lf ms%s\n", reply.received_bytes - sizeof(struct ip),
                       params.address, params.seq, reply_ttl, time, params.opts.bell);
            else
                printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%.2lf ms%s\n", reply.received_bytes - sizeof(struct ip),
                       params.address, params.seq, reply_ttl, time, params.opts.bell);
        }
        else
            printf("\b");
    }
    set_rtt_stats(time);
}

void wait_interval(struct timeval start)
{
    struct timeval interval;

    if (params.interval)
    {
        interval.tv_sec = start.tv_sec + (long)params.interval;
        interval.tv_usec = start.tv_usec + (long)((params.interval - (long)params.interval) * 1000000);
        while (timercmp(&start, &interval, <))
            set_time(&start);
    }
}

int check_c_opt()
{
    if (params.opts.count)
    {
        params.opts.count--;
        if (!params.opts.count)
            return (print_stats());
    }
    return (false);
}

void print_params()
{
    printf("flags %d\n", params.flags);
    printf("interval %f\n", params.interval);
    printf("user_requested_address %s\n", params.user_requested_address);
    printf("address %s\n", params.address);
    printf("reversed_address %s\n", params.reversed_address);
    printf("ttl %d\n", params.ttl);
    printf("process_id %d\n", params.process_id);
    printf("socket_fd %d\n", params.socket_fd);
    printf("sent_packets %d\n", params.sent_packets);
    printf("received_packets %d\n", params.received_packets);
    printf("error_packets %d\n", params.error_packets);
    printf("seq %d\n", params.seq);
    printf("start %f\n", params.start);
    printf("end %f\n", params.end);
    printf("packet_size %d\n", params.packet_size);
}

void ping(void)
{

    t_packet packet;
    struct timeval start;
    struct timeval end;

    if (params.socket_fd == -1)
        return;

    printf("PING %s (%s) %d(%d) bytes of data.\n",
           params.reversed_address,
           params.address,
           params.packet_size,
           params.packet_size + 28);
    params.start = get_time();
    // print_params();
    while (!params.quit)
    {
        set_time(&start);
        init_packet(&packet, start);
        if (send_packet(&packet))
        {
            init_reply(&params.reply);
            if (receive_reply(&params.reply))
            {
                params.received_packets++;
                set_time(&end);
                display_sequence(params.reply, calculate_elapsed_time(start, end));
            }
            else if (receive_reply(&params.reply) == TTL_EXCEEDED_CODE)
            {
                //		display_exceeded_sequence(reply);
                //		params.error_packets++;
            }
        }
        if (check_c_opt())
            break;
        params.seq++;
        params.opts.preload - 1 > 0 ? params.opts.preload-- : wait_interval(start);
    }
}

// options list
//  -v verbose
//  -h help

// -D timestamp before each line
// -n numeric output only
// -f flood ping with .
// -a bell
// -q quiet

// -c count request
// -i interval between send
// -l preload packets before anszer
// -t ttl
// -w timeout before end of ping
// -s packetsize

// f & i not handled probably
int parsing(int ac, char **av)
{
    if (ac < 2)
        ft_printerr_exit("ft_ping: usage error: Destination address required", 1);
    for (int i = 1; i < ac; i++)
    {
        if (av[i][0] == '-')
        {
            int flag = 1;
            for (int j = 1; av[i][j] && flag; j++)
            {
                switch (av[i][j])
                {
                case 'v':
                case 'D':
                case 'n':
                case 'f':
                case 'a':
                case 'q':
                    add_no_params_opt(av[i][j]);
                    break;
                case 'h':
                    return (help());
                case 'c':
                case 'i':
                case 'l':
                case 't':
                case 'w':
                case 's':
                    add_params_opt(av, &i, j, &flag);
                    break;
                default:
                    printf("ping: Invalid option -- '%c'\n", av[i][j]);
                    return (help());
                }
            }
        }
        else
        {
            params.user_requested_address = av[i];
            ft_getadress(params.user_requested_address);
            _checkOpt(); // for params
            addOptionsModifications();
            return (true);
        }
    }
    if (!params.user_requested_address)
        ft_printerr_exit("ft_ping: usage error: Destination address required", 2);
    return (true);
}

int main(int ac, char **av)
{
    init();
    if (parsing(ac, av))
    {
        initSignal();
        createSocket();
        ping();
    }
    return (0);
}
