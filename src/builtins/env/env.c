/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:15:02 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/10/14 11:58:11 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
// #include "../builtins.h"

int	ft_env(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (till_eq(env[i]) != -1)
		{
			ft_putstr_fd(env[i], fd);
			ft_putstr_fd("\n", fd);
		}
		i++;
	}
	return (1);
}
