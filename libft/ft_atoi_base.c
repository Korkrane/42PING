/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 11:37:09 by bahaas            #+#    #+#             */
/*   Updated: 2021/05/27 20:11:08 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_base(char *base)
{
	int	i;
	int	j;

	i = -1;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[++i])
	{
		j = i;
		while (base[++j])
		{
			if (base[i] == base[j])
				return (0);
		}
	}
	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || (base[i] == ' '
				|| base[i] == '\t' || base[i] == '\v'
				|| base[i] == '\n' || base[i] == '\r' || base[i] == '\f'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

long int	ft_parse_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\n' || str[i] == '\r' || str[i] == '\f')
		i++;
	return (i);
}

int	ft_atoi_base(char *str, char *base)
{
	long int	tot;
	long int	sign;
	long int	i;

	sign = 1;
	tot = 0;
	i = 0;
	if (ft_check_base(base) == 1)
	{
		i = ft_parse_whitespaces(str);
		while (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				sign *= -1;
			i++;
		}
		while (str[i] && ft_check_in_base(str[i], base) >= 0)
		{
			tot = tot * ft_strlen(base) + ft_check_in_base(str[i], base);
			i++;
		}
		return (tot * sign);
	}
	return (0);
}
