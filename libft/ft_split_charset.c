/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 14:34:39 by bahaas            #+#    #+#             */
/*   Updated: 2021/05/27 20:12:52 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count_word_w_charset(char *str, char *charset)
{
	int	i;
	int	w_count;
	int	w_length;

	i = 0;
	w_count = 0;
	while (str[i])
	{
		while (str[i] && is_charset(str[i], charset))
			i++;
		w_length = 0;
		while (str[i] && !is_charset(str[i], charset))
		{
			w_length++;
			i++;
		}
		if (w_length)
			w_count++;
	}
	return (w_count);
}

static char	*fill_str(char *new_str, char *old_str, int len_to_malloc)
{
	int	i;

	i = 0;
	while (old_str[i] && i < len_to_malloc)
	{
		new_str[i] = old_str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static char	**create_str(char *str, char *charset, int w_count, char **new_tab)
{
	int	i;
	int	j;
	int	w_len;

	i = 0;
	j = 0;
	while (i < w_count)
	{
		while (str[j] && is_charset(str[j], charset))
			j++;
		w_len = 0;
		while (str[j + w_len] && !is_charset(str[j + w_len], charset))
			w_len++;
		new_tab[i] = malloc(sizeof(char *) * (w_len + 1));
		if (!new_tab[i])
			return (NULL);
		fill_str(new_tab[i], &str[j], w_len);
		j += w_len;
		i++;
	}
	return (new_tab);
}

char	**ft_split_charset(char *str, char *charset)
{
	char	**new_tab;
	int		w_count;

	w_count = count_word_w_charset(str, charset);
	new_tab = malloc(sizeof(char *) * (w_count + 1));
	if (!new_tab)
		return (NULL);
	new_tab = create_str(str, charset, w_count, new_tab);
	new_tab[w_count] = 0;
	return (new_tab);
}
