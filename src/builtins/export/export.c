/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:17:51 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/24 15:40:55 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	not_exportable(char *str)
{
	ft_putstr_fd("shell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (0);
}

int	is_exportable(char *str)
{
	int	i;

	i = 0;
	if (!ft_strlen(str))
		return (not_exportable(str));
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')))
		return (not_exportable(str));
	while (str[i] && str[i] != '=')
	{
		if (!is_var(str[i]))
			return (not_exportable(str));
		i++;
	}
	return (1);
}

void	exprt_new(char *str, char ***env, int size)
{
	char	**new_env;
	int		i;

	i = -1;
	if (!is_exportable(str))
		return ;
	new_env = malloc(sizeof(char *) * (size + 2));
	while (++i < size)
		new_env[i] = ft_strdup((*env)[i]);
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	free_matrix(*env);
	*env = new_env;
}

void	export_args(char *str, char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if ((till_eq((*env)[i]) == -1
			&& !ft_strncmp((*env)[i], str, ft_strlen((*env)[i]))))
			return (export_args_utils2(str, env, i));
		if (!ft_strncmp((*env)[i], str, till_eq((*env)[i])))
		{
			if (!str[till_eq((*env)[i])])
			{
				free(str);
				return ;
			}
			if (str[till_eq((*env)[i])] == '=')
				break ;
		}
		i++;
	}
	export_args_utils2(str, env, i);
}

int	ft_export(char **args, char ***env, int fd)
{
	int	y;

	y = 1;
	if (matrix_size(args) == 1)
	{
		free_matrix(args);
		return (no_args(*env, fd));
	}
	while (args[y])
		export_args(ft_strdup(args[y++]), env);
	free_matrix(args);
	return (1);
}
