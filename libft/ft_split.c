/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:10:48 by bahaas            #+#    #+#             */
/*   Updated: 2021/05/27 19:55:30 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	w_len;
	int	count_w;

	i = 0;
	count_w = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		w_len = 0;
		while (str[i] && str[i] != c)
		{
			w_len++;
			i++;
		}
		if (w_len)
			count_w++;
	}
	return (count_w);
}

static char	*ft_strncat(char *str, char *new_str, int n)
{
	int	i;

	i = 0;
	while (str[i] && i < n)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static char	**ft_create(char **split, char c, int count_w, char *str)
{
	int	i;
	int	j;
	int	w_len;

	i = 0;
	j = 0;
	while (i < count_w)
	{
		while (str[j] && str[j] == c)
			j++;
		w_len = 0;
		while (str[j + w_len] && str[j + w_len] != c)
			w_len++;
		split[i] = malloc(sizeof(char *) * w_len + 1);
		if (!split[i])
			return (NULL);
		ft_strncat(&str[j], split[i], w_len);
		j += w_len;
		i++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		count_w;
	char	**split;

	if (!s)
		return (NULL);
	count_w = count_words((char *)s, c);
	split = malloc(sizeof(char *) * (count_w + 1));
	if (!split)
		return (NULL);
	split = ft_create(split, c, count_w, (char *)s);
	split[count_w] = 0;
	return (split);
}
