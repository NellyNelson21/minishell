/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darlene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:55:06 by darlene           #+#    #+#             */
/*   Updated: 2021/11/06 18:14:57 by darlene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_trim_from_start(char *s, char const *set)
{
	int	i;
	int	j;
	int	find;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		find = 0;
		while (set[j] != '\0')
		{
			if (s[i] == set[j] && !find)
				find = 1;
			j++;
		}
		if (!find)
			break ;
		i++;
	}
	return ((char *)(s + i));
}

static int	ft_trim_from_end(char *s, char const *set)
{
	int	i;
	int	j;
	int	find;

	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		j = 0;
		find = 0;
		while (set[j] != '\0')
		{
			if (s[i] == set[j] && !find)
				find = 1;
			j++;
		}
		if (!find)
			break ;
		i--;
	}
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	char	*s2;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	s = (char *)s1;
	s = ft_trim_from_start(s, set);
	len = ft_trim_from_end(s, set);
	s2 = malloc(len + 1);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s, len + 1);
	free((char *)s1);
	return ((char *)s2);
}
