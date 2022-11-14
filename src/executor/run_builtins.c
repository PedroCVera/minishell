/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:03:55 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/24 16:00:40 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	built_error(char *str)
{
	ft_putstr_fd("Error: couldn't open file: ", 2);
	ft_putstr_fd(str, 2);
	free(str);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int	redirect_out(t_tree *tree)
{
	t_exec	e;
	int		fd;
	int		i;

	i = 0;
	e.out = count_redirect(tree, 0, OUT);
	while (tree)
	{
		if (tree->id == OUT || tree->id == APD)
		{
			if (tree->id == OUT)
				fd = open(tree->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(tree->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			i++;
			if (fd == -1)
				return (built_error(tree->str));
			if (i != e.out)
				close(fd);
			else
				return (fd);
		}
		tree = tree->left;
	}
	return (1);
}

int	run_builtin(t_tree *tree, char ***env, char *cmd, int fd)
{
	if (cmd && !ft_strncmp(cmd, "exit", ft_strlen("exit") + 1))
		return (ft_exit(get_args(tree, 0)));
	if (cmd && !ft_strncmp(cmd, "env", ft_strlen("env") + 1))
		return (ft_env(*env, fd));
	if (cmd && !ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1))
		return (ft_pwd(fd));
	if (cmd && !ft_strncmp(cmd, "echo", ft_strlen("echo") + 1))
		return (ft_echo(get_args(tree, 0), fd));
	if (cmd && !ft_strncmp(cmd, "export", ft_strlen("export") + 1))
		return (ft_export(get_args(tree, 0), env, fd));
	if (cmd && !ft_strncmp(cmd, "unset", ft_strlen("unset") + 1))
		return (ft_unset(get_args(tree, 0), env));
	if (cmd && !ft_strncmp(cmd, "cd", ft_strlen("cd") + 1))
		return (ft_cd(get_args(tree, 0), env));
	if (fd > 2)
		close(fd);
	return (0);
}

int	check_builtin2(t_tree *tree, char ***env, char *cmd)
{
	int	fd;

	if (cmd && (!ft_strncmp(cmd, "exit", ft_strlen("exit") + 1)
			|| !ft_strncmp(cmd, "env", ft_strlen("env") + 1)
			|| !ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1)
			|| !ft_strncmp(cmd, "echo", ft_strlen("echo") + 1)
			|| !ft_strncmp(cmd, "export", ft_strlen("export") + 1)
			|| !ft_strncmp(cmd, "unset", ft_strlen("unset") + 1)
			|| !ft_strncmp(cmd, "cd", ft_strlen("cd") + 1)))
	{
		if (redirect_in(tree))
			return (1);
		fd = redirect_out(tree);
		run_builtin(tree, env, cmd, fd);
		return (1);
	}
	return (0);
}

int	check_builtin(t_tree *tree, char ***env, char *cmd, int pos)
{
	int	fd;

	fd = 1;
	if (cmd && !ft_strncmp(cmd, "exit", ft_strlen("exit") + 1))
		return (ft_exit(get_args(tree, pos)));
	if (cmd && !ft_strncmp(cmd, "env", ft_strlen("env") + 1))
		return (ft_env(*env, fd));
	if (cmd && !ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1))
		return (ft_pwd(fd));
	if (cmd && !ft_strncmp(cmd, "echo", ft_strlen("echo") + 1))
		return (ft_echo(get_args(tree, pos), fd));
	if (cmd && !ft_strncmp(cmd, "export", ft_strlen("export") + 1))
		return (ft_export(get_args(tree, pos), env, fd));
	if (cmd && !ft_strncmp(cmd, "unset", ft_strlen("unset") + 1))
		return (ft_unset(get_args(tree, pos), env));
	if (cmd && !ft_strncmp(cmd, "cd", ft_strlen("cd") + 1))
		return (ft_cd(get_args(tree, pos), env));
	return (0);
}
