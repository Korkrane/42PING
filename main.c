/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:03:59 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/13 12:18:53 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ping.h"

int quit = 0;

void error_output(char *message)
{
    fprintf(stderr, "%s\n", message);
}

void error_output_and_exit(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void ft_getadress(char *host_name, t_params *params)
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
    params->reversed_address = res->ai_canonname;
    ft_memcpy(&params->sockaddr, res->ai_addr, sizeof(struct sockaddr_in));
    inet_ntop(AF_INET, &(params->sockaddr.sin_addr), address, INET_ADDRSTRLEN);
    params->address = ft_strdup(address);
}

// options list
//  -v verbose
//  -h help

int help()
{
    fprintf(stderr, "\nUsage\n  ping [options] <destination>\n"
                    "\nOptions:\n"
                    "  <destinaton>\t     dns name or ip address\n"
                    "  -h\t\t     print help and exit\n"
                    "  -v\t\t     verbose output\n");
    return 0;
}

int parsing(int ac, char **av, t_params *params)
{
    if (ac < 2)
    {
        fprintf(stderr, "ping: usage error: Destination address required\n");
        exit(1);
    }
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
                    add_no_params_opt(av[i][j], *params);
                    break;
                case 'h':
                    return (help());
                default:
                    printf("ping: Invalid option -- '%c'\n", av[i][j]);
                    return (help());
                }
            }
        }
        else
        {
            // printf("value: %s\n", av[i]);
            params->user_requested_address = ft_strdup(av[i]);
            _checkOpt(*params); // for debug :)
            return true;
        }
    }
    return true;
}

void ping_loop(t_params *params)
{
    t_packet packet;
    struct timeval start;
    struct timeval end;

    while (!quit)
    {
        set_time(&start);
        init_packet(&packet, start, params);
        if (send_packet(&packet, params))
        {
            // 	init_reply(&params.reply);
            // 	if (receive_reply(&params.reply))
            // 	{
            // 		params.received_packets++;
            // 		set_time(&end);
            // 		display_sequence(params.reply, calculate_elapsed_time(start, end));
            // 	}
            // 	else if (receive_reply(&params.reply) == TTL_EXCEEDED_CODE)
            // 	{
            // 		//		display_exceeded_sequence(reply);
            // 		//		params.error_packets++;
            // 	}
        }
        // if(check_c_opt())
        // 	break;
        // params.seq++;
        // params.opts.preload - 1 > 0 ? params.opts.preload-- : wait_interval(start);
    }
    print_stats(params);
}

int main(int ac, char **av)
{
    t_params params;

    if (parsing(ac, av, &params))
    {
        if (!params.user_requested_address)
        {
            fprintf(stderr, "Dping: usage error: Destination address required\n");
            exit(2);
        }
        else
        {
            init(ac, av, &params);
            set_signal();
            if (params.address)
                create_socket(&params);
            if (params.socket_fd != -1)
            {
                printf("PING %s (%s) %d(%d) bytes of data.\n",
                       params.reversed_address,
                       params.address,
                       params.packet_size,
                       params.packet_size + 28);
                params.start = get_time();
                // ping_loop();
            }
            ping_loop(&params);
            printf("Everything ok\n");
        }
    }
    return 0;
}