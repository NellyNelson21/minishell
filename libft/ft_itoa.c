/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darlene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:12:15 by darlene           #+#    #+#             */
/*   Updated: 2021/10/13 16:12:17 by darlene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char	*dest, char	*src)
{
	int	index;

	index = 0;
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index += 1;
	}
	dest[index] = '\0';
	return (dest);
}

static int	ft_get_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static int	ft_set_pow(int count)
{
	int	pow;

	pow = 1;
	while (count > 1)
	{
		pow *= 10;
		count--;
	}
	return (pow);
}

static char	*set_number(int n, int count, char *number)
{
	int	i;
	int	del;
	int	pow;

	i = 0;
	pow = ft_set_pow(count);
	if (n < 0)
	{
		number[0] = '-';
		i = 1;
		n *= -1;
	}
	while (pow > 0)
	{
		del = n / pow;
		number[i] = del + '0';
		n = n % pow;
		pow /= 10;
		i++;
	}
	number[i] = '\0';
	return (number);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*number;

	if (n == -2147483648)
	{
		number = malloc(12);
		if (!number)
			return (NULL);
		return (ft_strcpy(number, "-2147483648"));
	}
	count = ft_get_count(n);
	if (n < 0)
	{
		number = malloc(count + 2);
		if (!number)
			return (NULL);
	}
	else
	{
		number = malloc(count + 1);
		if (!number)
			return (NULL);
	}
	number = set_number(n, count, number);
	return (number);
}
