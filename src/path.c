/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:06:21 by marvin            #+#    #+#             */
/*   Updated: 2022/08/02 22:06:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	**get_path(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (!ft_strncmp(env[i], "PATH=", 5))
// 			return (ft_split(env[i] + 5, ':'));
// 		i++;
// 	}
// 	return (NULL);
// }

// void	check_cmd(char *cmd, char **path)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*cmd2

// 	cmd2 = ft_strjoin("/", cmd);
// 	free(cmd);
// 	i = 0;
// 	while (path[i])
// 	{
// 		tmp = ft_strjoin(path[i], cmd2)
// 		if (access(tmp, X_OK))
// 			return ;
// 		i++;
// 		free(tmp);
// 	}
// 	//If it reaches here, the command does not exist
// }

// void	child_process(t_pipex *p, int i, char **env)
// {
// 	if (pipe(p->pipe) == -1)
// 		ft_err(p, "Error");
// 	p->pid = fork();
// 	if (p->pid < 0)
// 		ft_err(p, "Error");
// 	if (!p->pid)
// 	{
// 		close(p->pipe[0]);
// 		if (p->id == 0)
// 			infile_norm(p);
// 		else if (p->id == p->cmdnbr - 1)
// 			dup2(p->outfile, STDOUT_FILENO);
// 		else
// 			dup2(p->pipe[1], STDOUT_FILENO);
// 		child_work(p, i);
// 		execve(p->cmdpath, p->cmd, env);
// 		free_all(p);
// 		exit(127);
// 	}
// 	close(p->pipe[1]);
// 	dup2(p->pipe[0], STDIN_FILENO);
// 	close(p->pipe[0]);
// }
