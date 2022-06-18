/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 18:57:14 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/18 18:22:57 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

static void printLimitsErrorAndExit(long long min, long long max, long long val)
{
	if(max == LLONG_MAX && val > 0)
		printf("ft_ping: invalid argument: '%lld': Numerical result out of range\n", val);
	else
		printf("ft_ping: invalid argument: '%lld': out of range: %lld <= value <= %lld\n", val, min, max);
	exit(1);
}

static void setValue(long long *value, char *str)
{
	if (ft_strcmp(str, "9223372036854775808") == 0)
		*value = atoll(str) + 1;
	else
		*value = atoll(str);
}

static void checkLimits(long long value, long long min_limit, long long max_limit)
{
	if (value < min_limit || value > max_limit)
		printLimitsErrorAndExit(min_limit, max_limit, value);
}

static void checkStringIsNumber(char *str)
{
	if (!ft_isnbr(str))
		ft_printerr_exit(ft_strjoin("ft_ping: invalid argument: ", str), 1);
}

static long long getValue(long long min_limit, long long max_limit, char *str)
{
	long long value;

	checkStringIsNumber(str);
	setValue(&value, str);
	checkLimits(value, min_limit, max_limit);
	return value;
}

static int valueIsNextArg(char **av, int *i, int j)
{
	if (av[*i][j + 1] == '\0' && av[*i + 1] != NULL)
		return true;
	return false;
}

static int valueIsNextToOptArg(char **av, int *i, int j)
{
	if (ft_isdigit(av[*i][j + 1]) || av[*i][j + 1] == '-')
		return true;
	return false;
}

static long long setOptValue(char **av, int *i, int j, long long min_limit, long long max_limit)
{
	char *strValue = 0;

	if (valueIsNextArg(av, i, j))
	{
		strValue = av[*i + 1];
		++*i;
	}
	else if (valueIsNextToOptArg(av, i, j))
		strValue = &av[*i][j + 1];
	return getValue(min_limit, max_limit, strValue);
}

void addParamWithoutValue(char opt)
{
	switch(opt)
	{
		case 'v': params.flags |= v; break; //verbose mode
		case 'D': params.flags |= D; break; //timestamp on each line
		case 'n': params.flags |= n; break; //display only ip address (on each)
		case 'f': params.flags |= f; break; //flood (print . on send and \b on receive) + interval = 0 unless specified
		case 'a': params.flags |= a; break; //bell song on each line
		case 'q': params.flags |= q; break; //quiet ouput
	}
}

void addParamWithValue(char **av, int *j, int k, int *flag)
{
	switch(av[*j][k])
	{
		case 'c': params.flags |= c; params.opts.count = setOptValue(av, j, k, 1, LLONG_MAX); *flag = 0; break; //count limit packet to send
		//case 'i': params.flags |= i; params.opts.interval = setOptValue(av, j, k, 0, INT_MAX / 1000); *flag = 0; break; //set new interval
		// case 'l': params.flags |= l; get_preload(av, i, k); *flag = 0; break; //set preload packet to send
		// case 't': params.flags |= t; get_ttl(av, i, k, UCHAR_MAX); *flag = 0; break; //set new ttl
		// case 's': params.flags |= s; get_packetsize(av, i, k, 127992, USHRT_MAX + 1); *flag = 0; break; //set new packet size
		//case 'w': params.flags |= w; get_deadline(av, i, k, INT_MAX); *flag = 0; break; //set global deadline
	}
}