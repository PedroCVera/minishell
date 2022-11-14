/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:22:19 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/08 16:34:47 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

		// str = readline("\e[1;95mheredoc> \e[0m");

void	heredoc_filler_utils2(char *eof, char *line)
{
	free(eof);
	if (line)
		free(line);
	exit(0);
}

void	heredoc_filler(int fd, char *eof, int exit_stat)
{
	char	*line;
	char	*str;

	while (1)
	{
		call_sigact(SI_HDOC);
		str = readline("heredoc> ");
		if (!str)
			heredoc_filler_utils(str, eof, exit_stat);
		line = ft_strjoin(str, "\n");
		free(str);
		if (line)
		{
			if (!ft_strlen(line))
				break ;
			if (!ft_strncmp(line, eof, ft_strlen(eof)))
				break ;
			if (fd > 0)
				write(fd, line, ft_strlen(line));
			free(line);
		}
	}
	heredoc_filler_utils2(eof, line);
}

int	ft_heredoc(t_tree **tree, t_exec *e, int i)
{
	if (pipe((*tree)->pipe) == -1)
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
	{
		if (i == e->in)
			heredoc_filler(((*tree)->pipe)[1], \
			ft_strjoin((*tree)->str, "\n"), 129);
		else
			heredoc_filler(-1, ft_strjoin((*tree)->str, "\n"), 0);
	}
	return (wait_heredoc(tree, e));
}

int	check_heredoc(t_tree **tree, t_exec *e)
{
	t_tree	*ptr;
	int		i;

	ptr = *tree;
	i = 0;
	e->doc = 0;
	while (ptr)
	{
		if (ptr->id == IN || ptr->id == DOC)
		{
			i++;
			if (ptr->id == DOC)
				if (ft_heredoc(&ptr, e, i))
					return (1);
		}
		if (!(e->pos))
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	return (0);
}

int	handle_heredoc(t_tree **tree, t_exec *e)
{
	t_tree	*ptr;

	e->pos = 0;
	ptr = *tree;
	while (ptr)
	{
		if (!(e->pos == 1 && !(ptr->right)))
		{
			e->in = count_redirect(ptr, e->pos, IN);
			if (check_heredoc(&ptr, e) == 1)
				return (1);
		}
		if (e->pos)
			ptr = ptr->up;
		e->pos++;
	}
	return (0);
}
