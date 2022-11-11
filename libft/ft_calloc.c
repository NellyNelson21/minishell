/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darlene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:55:02 by darlene           #+#    #+#             */
/*   Updated: 2021/11/05 12:35:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	size_t	value;
	void	*array;

	if (__builtin_mul_overflow(count, size, &value))
		return (0);
	i = 0;
	array = (void *)malloc(size * count);
	if (array != NULL)
	{
		while (i < size * count)
		{
			((char *) array)[i] = (char) 0;
			i++;
		}
	}
	return (array);
}
