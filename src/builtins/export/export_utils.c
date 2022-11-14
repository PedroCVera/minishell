/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:13:04 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/21 12:23:07 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	no_args(char **env, int fd)
{
	int	y;

	y = 0;
	while (env[y])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env[y], fd);
		ft_putstr_fd("\n", fd);
		y++;
	}
	return (1);
}

void	export_args_utils(char *str, char ***env, int i)
{
	free((*env)[i]);
	(*env)[i] = ft_strdup(str);
	free(str);
}

void	export_args_utils2(char *str, char ***env, int i)
{
	if (!((*env)[i]))
		exprt_new(str, env, i);
	else
	{
		free((*env)[i]);
		(*env)[i] = ft_strdup(str);
	}
	free(str);
}
