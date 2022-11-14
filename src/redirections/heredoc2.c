/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 07:52:46 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/08 16:32:19 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	wait_heredoc(t_tree **tree, t_exec *e)
{
	int	stat;

	close(((*tree)->pipe)[1]);
	waitpid(e->pid, &stat, 0);
	update_status(stat);
	if (g_status == 129 || g_status == 130)
	{
		if (g_status == 129)
			g_status = 0;
		return (1);
	}
	return (0);
}

void	heredoc_filler_utils(char *str, char *eof, int exit_stat)
{
	ft_putstr_fd("\nshell: warning: here-document delimited ", 1);
	ft_putstr_fd("by end-of-file (wanted `", 1);
	write(1, eof, ft_strlen(eof) - 1);
	ft_putstr_fd("')\n", 1);
	free(eof);
	free(str);
	unlink(".heredoc_tmp");
	exit(exit_stat);
}

void	no_heredoc_utils(t_tree *tree, t_exec *e, int i)
{
	int	fd;

	fd = open(tree->str, O_RDONLY, 0644);
	if (fd == -1)
		in_error(tree->str);
	if (i != e->in)
		close(fd);
	else
		dup2(fd, STDIN_FILENO);
}
