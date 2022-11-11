/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darlene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:49:50 by darlene           #+#    #+#             */
/*   Updated: 2021/10/09 17:49:52 by darlene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dst && !src)
		return (NULL);
	if ((unsigned char *)src < (unsigned char *)dst)
	{
		while (n--)
			((unsigned char *) dst)[n] = ((unsigned char *) src)[n];
	}
	else
	{
		while (++i < n)
			((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
	}
	return (dst);
}
