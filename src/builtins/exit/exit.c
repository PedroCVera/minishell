/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:30:16 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/10/21 14:31:51 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_nbr(char *str)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (!nbr)
			nbr = 1;
		i++;
	}
	if (!str[i] && nbr)
		return (1);
	return (0);
}

int	exit_continue(char **args, int nbr);

int	matrix_size(char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y])
		y++;
	return (y);
}

int	ft_exit(char **args)
{
	int	nbr;

	nbr = 0;
	if (args[1] && is_nbr(args[1]))
		nbr = 1;
	if ((nbr && matrix_size(args) == 2) || matrix_size(args) == 1)
	{
		ft_putstr_fd("exit\n", 2);
		if (nbr)
		{
			g_status = (unsigned int) ft_atoi(args[1]);
			free_matrix(args);
			rl_clear_history();
			exit(g_status);
		}
		free_matrix(args);
		rl_clear_history();
		exit(g_status);
	}
	return (exit_continue(args, nbr));
}

int	exit_continue(char **args, int nbr)
{
	if (nbr && args[2])
	{
		ft_putstr_fd("shell: exit: too many arguments\n", 2);
		g_status = 1;
		free_matrix(args);
		return (-1);
	}
	g_status = 2;
	ft_putstr_fd("exit\nshell: exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_matrix(args);
	rl_clear_history();
	exit(2);
	return (-69);
}
