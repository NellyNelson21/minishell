/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darlene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:54:51 by darlene           #+#    #+#             */
/*   Updated: 2021/11/06 18:46:11 by darlene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_issign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

static int	ft_check_overflow(int sign)
{
	if (sign > 0)
		return (-1);
	return (0);
}

static void	ft_set_sign(char c, int *sign)
{
	if (c == '-')
		*sign = -1;
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	result_ll;
	int					result;
	int					sign;

	i = 0;
	result_ll = 0;
	result = 0;
	sign = 1;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] != '\0' && ft_issign(str[i]) && str[i])
	{
		ft_set_sign(str[i], &sign);
		i++;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		result_ll = result_ll * 10 + (str[i] - '0');
		result = result * 10 + sign * (str[i] - '0');
		if (result_ll > LLONG_MAX)
			return (ft_check_overflow(sign));
		i++;
	}
	return (result);
}
