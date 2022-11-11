/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:34:42 by nnelson           #+#    #+#             */
/*   Updated: 2022/07/31 22:09:37 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    if (ft_strlen(s1) != ft_strlen(s2))
        return (1);
    else
    {
        while (s1[i] != '\0' || s2[i] != '\0')
        {
            if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
                return (1);
            i++;
        }
    }
    return (0);
}
