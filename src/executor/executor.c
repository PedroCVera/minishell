/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:53:57 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/08 15:50:01 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_process(t_tree *tree, t_exec *e, int *fd)
{
	close((e->p)[0]);
	redirections(tree, e, fd);
	call_sigact(SI_DFL);
	rl_clear_history();
	if (check_builtin(tree, e->env, find_command(tree, e->pos), e->pos))
		exit(g_status);
	execve(cmd_path(find_command(tree, e->pos), *(e->env)),
		get_args(tree, e->pos), *(e->env));
	free_tree(free_tree_utils(&tree));
	exit(127);
}

void	executor(t_tree *tree, t_exec *e, int *fd)
{
	if (pipe(e->p) == -1)
	{
		ft_putstr_fd("Error: couldn't open pipe\n", 2);
		g_status = 1;
		exit(1);
	}
	e->pid = fork();
	if (e->pid < 0)
	{
		ft_putstr_fd("Error: couldn't create a new process\n", 2);
		g_status = 1;
		exit(1);
	}
	if (!(e->pid))
		child_process(tree, e, fd);
	if (e->count != 1)
	{
		if ((*fd) > 0)
			close(*fd);
		close((e->p)[1]);
		*fd = (e->p)[0];
	}
}

t_exec	execute_command(t_tree	*tree, int pos, int count, char ***env)
{
	t_exec		e;
	static int	fd;

	if (!pos)
		fd = 0;
	e.env = env;
	e.count = count;
	e.pos = pos;
	executor(tree, &e, &fd);
	return (e);
}

void	update_status(int val2)
{
	if (WIFSIGNALED(val2))
	{
		g_status = WTERMSIG(val2) + 128;
		if (g_status == 130)
			write(1, "\n", 1);
	}
	else
		g_status = WEXITSTATUS(val2);
}

void	execute_tree(t_tree **tree, char ***env)
{
	t_tree	*ptr;
	int		i;
	int		val2;
	int		count;
	t_exec	e;

	i = 0;
	if (execute_tree_utils(tree, &e, &i, &count))
		return ;
	if (count == 1 && check_builtin2(*tree, env, find_command(*tree, 0)))
		return ;
	ptr = *tree;
	while (ptr)
	{
		if (!(i == 1 && !(ptr->right)))
			e = execute_command(ptr, i, count, env);
		if (i)
			ptr = ptr->up;
		i++;
	}
	waitpid(e.pid, &val2, 0);
	update_status(val2);
	i = -1;
	while (++i < count)
		wait(NULL);
}
