/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 22:52:12 by bahaas            #+#    #+#             */
/*   Updated: 2021/05/27 20:04:39 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_tot_len(char const *s1, char const *s2)
{
	int	tot_len;

	tot_len = 0;
	tot_len += ft_strlen(s1) + ft_strlen(s2);
	return (tot_len);
}

static char	*ft_strcat(char *dest, char const *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

static void	ft_create(char *newstr, char const *s1, char const *s2)
{
	ft_strcat(newstr, s1);
	ft_strcat(newstr, s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*fillstr;
	int		tot_len;
	char	*emptystr;

	if (!s1 || !s2)
		return (NULL);
	tot_len = ft_tot_len(s1, s2);
	if (tot_len == 0)
	{
		emptystr = malloc(sizeof(char) * 1);
		emptystr[0] = '\0';
		return (emptystr);
	}
	fillstr = malloc(sizeof(char) * tot_len + 1);
	if (!fillstr)
		return (NULL);
	fillstr[0] = '\0';
	ft_create(fillstr, s1, s2);
	fillstr[tot_len] = '\0';
	return (fillstr);
}
