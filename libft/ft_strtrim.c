/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:33:16 by bahaas            #+#    #+#             */
/*   Updated: 2021/05/27 20:01:32 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_charset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	start_position(char const *s1, char const *set)
{
	int	pos;

	pos = 0;
	while (is_in_charset(s1[pos], set))
		pos++;
	return (pos);
}

static int	end_position(char const *s1, char const *set)
{
	int	pos;

	pos = ft_strlen(s1) - 1;
	while (is_in_charset(s1[pos], set))
		pos--;
	return (pos);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		trim_len;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	str = NULL;
	start = start_position(s1, set);
	end = end_position(s1, set);
	trim_len = end - start + 1;
	if (trim_len < 0)
		return (ft_calloc(1, 1));
	str = malloc(sizeof(char) * trim_len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i <= trim_len)
	{
		str[i] = s1[i + start];
		i++;
	}
	str[trim_len] = '\0';
	return (str);
}
