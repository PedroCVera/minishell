/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:16:28 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/11 17:24:14 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	not_unsetable(char *str)
{
	ft_putstr_fd("shell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (0);
}

int	is_unsetable(char *str)
{
	int	i;

	i = 0;
	if (!ft_strlen(str))
		return (not_unsetable(str));
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')))
		return (not_unsetable(str));
	while (str[i])
	{
		if (!is_var(str[i]))
			return (not_unsetable(str));
		i++;
	}
	return (1);
}

void	unset_args_utils(char ***env, char ***new_env, char *str)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], str, till_eq((*env)[i])))
		{
			(*new_env)[i2] = ft_strdup((*env)[i]);
			i2++;
		}
		i++;
	}
	(*new_env)[i2] = NULL;
}

void	unset_args(char *str, char ***env)
{
	char	**new_env;
	int		i;

	i = 0;
	if (!is_unsetable(str))
		return ;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], str, ft_strlen(str)) &&
			(!((*env)[i][ft_strlen(str)])
			|| ((*env)[i][ft_strlen(str)]) == '='))
		{
			new_env = malloc(sizeof(char *) * matrix_size(*env));
			unset_args_utils(env, &new_env, str);
			free_matrix(*env);
			*env = new_env;
			return ;
		}
		i++;
	}
}

int	ft_unset(char **args, char ***env)
{
	int	y;

	y = 0;
	while (args[++y])
		unset_args(args[y], env);
	free_matrix(args);
	return (1);
}
