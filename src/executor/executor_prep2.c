/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_prep2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:29:14 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/09 12:17:20 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*not_absolute(char *cmd, char **path, int i)
{
	char		*tmp;
	char		*pwd;
	char		*pwd2;

	if (cmd[0] && cmd[0] == '.')
	{
		pwd = getcwd(NULL, 0);
		pwd2 = ft_strjoin(pwd, "/");
		free(pwd);
		tmp = ft_strjoin(pwd2, cmd);
		if (check_path(cmd, tmp, path))
			return (tmp);
	}
	no_path(path);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (check_path(cmd, tmp, path))
			return (tmp);
	}
	if (check_slash(cmd))
		command_error("shell: No such file or directory: ", cmd, 127);
	command_error("shell: command not found: ", cmd, 127);
	return (NULL);
}

char	*absolute(char *cmd)
{
	DIR	*dirptr;

	dirptr = opendir (cmd);
	if (dirptr)
	{
		closedir(dirptr);
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		g_status = 126;
		exit(126);
	}
	if (access(cmd, X_OK) < 0)
	{
		ft_putstr_fd("shell: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		g_status = 127;
		exit(127);
	}
	return (cmd);
}

char	*cmd_path(char *cmd, char **env)
{
	if (!cmd)
		return (NULL);
	if (ft_strlen(cmd) == 1 && cmd[0] == '.')
	{
		ft_putstr_fd("shell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		g_status = 126;
		exit(126);
	}
	if (ft_strlen(cmd) == 2 && cmd[0] == '.' && cmd[1] == '.')
		command_error("shell: command not found: ", cmd, 127);
	if (cmd[0] == '/')
		return (absolute(cmd));
	else
		return (not_absolute(cmd, get_path(env), -1));
}

int	nbr_args(t_tree	*tree, int pos)
{
	int	count;

	count = 0;
	while (tree)
	{
		if (tree->id == ARG || tree->id == FLG || tree->id == CMD)
		{
			count++;
		}
		if (!pos)
			tree = tree->left;
		else
			tree = tree->right;
	}
	return (count);
}

char	**get_args(t_tree *tree, int pos)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (nbr_args(tree, pos) + 1));
	i = 0;
	while (tree)
	{
		if (tree->id == ARG || tree->id == FLG || tree->id == CMD)
		{
			args[i++] = ft_strdup(tree->str);
		}
		if (!pos)
			tree = tree->left;
		else
			tree = tree->right;
	}
	args[i] = 0;
	return (args);
}
