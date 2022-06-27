/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 16:53:09 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/24 16:50:50 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

int help()
{
    fprintf(stderr, "\nUsage\n  ping [options] <destination>\n"
                    "\nOptions:\n"
                    "  <destinaton>\t     dns name or ip address\n"
                    "  -h\t\t     print help and exit\n"
                    "  -v\t\t     verbose output\n");
    return 0;
}

void setAddress(char *host_name)
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
        fprintf(stderr, "ping: %s: Name or service not known\n", host_name);
        exit(2);
    }
    params.reversed_address = res->ai_canonname;
    ft_memcpy(&params.sockaddr, res->ai_addr, sizeof(struct sockaddr_in));
    inet_ntop(AF_INET, &(params.sockaddr.sin_addr), address, INET_ADDRSTRLEN);
    printf("address: %s\n", address);
    printf("reversed: %s\n", res->ai_canonname);
    params.address = ft_strdup(address);
}

void print_params()
{
    printf("flags %d\n", params.flags);
    printf("interval %f\n", params.interval);
    printf("requestedAddress %s\n", params.requestedAddress);
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

    printf("icmp %zu\n", sizeof(struct icmp));
    printf("icmphdr %zu\n", sizeof(struct icmphdr));
    printf("iphdr %zu\n", sizeof(struct iphdr));
    printf("ip %zu\n", sizeof(struct ip));
    printf("t_packet %zu\n", sizeof(t_packet));
    printf("----------------\n");
}

void ping(void)
{
    params.start = getTime();
    while (!params.quit)
    {
        t_packet packet;
        struct timeval start;
        struct timeval end;

        initPacket(&packet);
        setTime(&start);
        if (sendPacket(&packet))
        {
            initReply(&params.reply);
            if (recvReply(&params.reply))
            {
                params.received_packets++;
                setTime(&end);
                printReplyInfos(params.reply, getTimeDiff(start, end));
            }
            else if (recvReply(&params.reply) == TTL_EXCEEDED_CODE)
            {
                //		display_exceeded_sequence(reply);
                //		params.error_packets++;
            }
        }
        if (hasOptionEnabled(c) && hasReachedCountLimit())
            break;
        params.seq++;
        params.opts.preload - 1 > 0 ? params.opts.preload-- : waitForInterval(start);
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
        printErrorAndExit("ft_ping: usage error: Destination address required", 1);
    for (int i = 1; i < ac; i++)
    {
        if (av[i][0] == '-')
        {
            int flag = 1;
            for (int j = 1; av[i][j] && flag; j++)
            {
                switch (av[i][j])
                {
                case 'v': case 'D': case 'n': case 'f': case 'a': case 'q':
                    addParamWithoutValue(av[i][j]);
                    break;
                case 'h':
                    return (help());
                    // case 'l':
                    // case 't':
                    // case 's':
                //case 'i':
                case 'c': case 'w':
                    addParamWithValue(av, &i, j, &flag);
                    break;
                default:
                    printf("ping: Invalid option -- '%c'\n", av[i][j]);
                    return (help());
                }
            }
        }
        else
        {
            params.requestedAddress = av[i];
            setAddress(params.requestedAddress);
            checkOptDebug();
            addOptionsModifications();
            return (true);
        }
    }
    if (!params.requestedAddress)
        printErrorAndExit("ft_ping: usage error: Destination address required", 2);
    return (true);
}

int main(int ac, char **av)
{
    init();
    if (parsing(ac, av))
    {
        print_params();
        initSignal();
        if(params.address)
            params.socket_fd = createSocket();
        printPingInfo();
        ping();
    }
    return (0);
}
