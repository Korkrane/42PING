/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:59:47 by bahaas            #+#    #+#             */
/*   Updated: 2022/05/30 17:07:13 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char *ft_strcpy_join(char *dest, const char *src)
{
    size_t i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
    return (dest);
}

static char *ft_strncat_join(char *dest, const char *src, size_t n)
{
    size_t i;
    size_t j;

    i = 0;
    while (dest[i])
        i++;
    j = 0;
    while (src[j] && j < n)
        dest[i++] = src[j++];
    dest[i] = 0;
    return (dest);
}

// char *ft_strjoin(char const *s1, char const *s2)
char *ft_strjoins(char **strs)
{
    char *str;
    // size_t len_s1_s2;
    size_t len = 0;

    // i = 0;
    // if (!s1 || !s2)
    //     return (NULL);
    // len_s1_s2 = ft_strlen(s1) + ft_strlen(s2) + 1;
    int i = 0;
    while (strs[i])
    {
        len += strlen(strs[i]);
        i++;
    }
    str = (char *)malloc(sizeof(char) * (len));
    if (!str)
        return (NULL);
    ft_bzero(str, len);
    ft_strcpy_join(str, strs[0]);
    i = 1;
    while (strs[i])
    {
        ft_strncat_join(str, strs[i], ft_strlen(strs[i]));
        i++;
    }
    // ft_strncat_join(str, s2, ft_strlen(s2));
    return (str);
}
