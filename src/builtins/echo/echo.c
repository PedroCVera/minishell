/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:24:08 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/11/08 15:24:27 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	check_flag(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if ((!i && arg[i] != '-') || (i && arg[i] != 'n'))
			return (0);
	}
	return (1);
}

int	ft_echo(char **args, int fd)
{
	int	y;

	y = 1;
	if (matrix_size(args) > 1 && check_flag(args[1]))
		y++;
	while (args[y])
	{
		ft_putstr_fd(args[y], fd);
		if (args[y + 1])
			ft_putstr_fd(" ", fd);
		y++;
	}
	if (!(matrix_size(args) > 1 && check_flag(args[1])))
		ft_putstr_fd("\n", fd);
	free_matrix(args);
	g_status = 0;
	return (1);
}
