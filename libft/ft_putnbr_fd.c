/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darlene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:56:14 by darlene           #+#    #+#             */
/*   Updated: 2021/10/13 20:56:15 by darlene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

void	write_minus(int *n, int *fd, int *i)
{
	write(*fd, "-", 1);
	*i = 1;
	*n *= -1;
}

static void	ft_putstr(int n, int *fd)
{
	if (n == -2147483648)
		write(*fd, "-2147483648", 11);
	else if (n == 0)
		write(*fd, "0", 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	int		num;
	int		pow;
	char	c;

	if (!fd)
		return ;
	if (n == -2147483648 || n == 0)
	{
		ft_putstr(n, &fd);
		return ;
	}
	i = 0;
	pow = ft_set_pow(ft_get_count(n));
	if (n < 0)
		write_minus(&n, &fd, &i);
	while (pow > 0)
	{
		num = n / pow;
		c = num + '0';
		write(fd, &c, 1);
		n = n % pow;
		pow /= 10;
		i++;
	}
}
