/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:41:23 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/14 12:21:34 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*shell_lvl(char *str)
{
	char	*cpy;
	char	*new;

	cpy = ft_itoa(ft_atoi(str + 6) + 1);
	new = ft_strjoin("SHLVL=", cpy);
	free(cpy);
	return (new);
}

char	**get_env(char **env)
{
	int		i;
	char	**copy;

	i = 0;
	while (env[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
	{
		ft_putstr_fd("Error: couldn't allocate space\n", 2);
		exit(1);
	}
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
			copy[i] = shell_lvl(env[i]);
		else
			copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
