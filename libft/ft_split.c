/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darlene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 20:01:42 by darlene           #+#    #+#             */
/*   Updated: 2021/11/06 20:03:07 by darlene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_word_amount(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_get_word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static void	*ft_delete_array(char **array, int word_amount)
{
	int	i;

	i = 0;
	while (i < word_amount)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**ft_fill_array(char const *s, char c, char **array, int
word_amount)
{
	int	i;
	int	k;
	int	word_len;

	i = -1;
	while (++i < word_amount)
	{
		while (*s == c)
			s++;
		word_len = ft_get_word_len(s, c);
		array[i] = (char *)malloc((word_len + 1) * sizeof(char));
		if (!array[i])
			return (ft_delete_array(array, i));
		k = 0;
		while (k < word_len)
		{
			array[i][k] = *s;
			k++;
			s++;
		}
		array[i][k] = '\0';
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word_amount;

	if (!s)
		return (NULL);
	word_amount = ft_get_word_amount(s, c);
	array = (char **)malloc((word_amount + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = ft_fill_array(s, c, array, word_amount);
	return (array);
}
