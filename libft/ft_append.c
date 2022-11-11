/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnelson <nnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 19:25:43 by nnelson           #+#    #+#             */
/*   Updated: 2022/07/30 20:49:06 by nnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_append(char const *s1, char const c)
{
	int		i;
	char	*s;

	if (!s1 || !c)
		return (NULL);
	i = 0;
	s = malloc(ft_strlen(s1) + 2);
	if (!s)
		return (NULL);
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = c;
	i++;
	s[i] = '\0';
	free((char *)s1);
	return (s);
}
