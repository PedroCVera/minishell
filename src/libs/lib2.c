/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:11:52 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/26 14:49:25 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

long int	ft_atoi(const char *str)
{
	long int	i;
	long int	num;
	long int	neg;

	num = 0;
	neg = 1;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	if (str[i] == '+' && str[i - 1] != '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && neg != 0)
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * neg);
}

static int	num_size(int n)
{
	int	size;

	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*converter(int n, char *result, int size)
{
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
	}
	result[size - 1] = '\0';
	while (n > 0)
	{
		result[size - 2] = n % 10 + '0';
		n /= 10;
		size--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		num;
	int		size;

	num = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == -0)
		return (ft_strdup("0"));
	size = (num_size(num) + 1);
	result = malloc((size) * 1);
	if (!result)
		return (0);
	return (converter(n, result, size));
}
