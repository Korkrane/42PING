/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 22:52:08 by bahaas            #+#    #+#             */
/*   Updated: 2021/05/27 20:18:09 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(long i)
{
	int	count;

	count = 0;
	if (i == 0)
		return (1);
	while (i > 0)
	{
		i /= 10;
		count++;
	}
	return (count);
}

static char	*reverse(char *str)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	if (str[0] == '-')
		i++;
	while (str[j])
		j++;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j - 1];
		str[j - 1] = tmp;
		i++;
		j--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			i;
	int			tot_len;
	char		*str;

	nb = n;
	tot_len = 0;
	if (nb < 0)
	{
		nb = -nb;
		tot_len = 1;
	}
	tot_len += count_digit(nb);
	str = malloc(sizeof(char) * (tot_len + 1));
	i = 0;
	if (n < 0)
		str[i++] = '-';
	while (i < tot_len)
	{
		str[i++] = nb % 10 + '0';
		nb /= 10;
	}
	str[i] = '\0';
	return (reverse(str));
}
