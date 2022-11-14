/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:45:10 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/08 15:24:48 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_redirect(t_tree *tree, int pos, int id)
{
	int	count;

	count = 0;
	while (tree)
	{
		if (((tree->id == OUT || tree->id == APD) && id == OUT)
			|| ((tree->id == IN || tree->id == DOC) && id == IN))
			count++;
		if (!pos)
			tree = tree->left;
		else
			tree = tree->right;
	}
	return (count);
}

void	in_error(char *str)
{
	ft_putstr_fd("Error: couldn't open file: ", 2);
	ft_putstr_fd(str, 2);
	free(str);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	open_in(t_tree *tree, t_exec *e)
{
	int	i;

	i = 0;
	e->doc = 0;
	while (tree)
	{
		if (tree->id == IN || tree->id == DOC)
		{
			i++;
			if (tree->id == IN)
				no_heredoc_utils(tree, e, i);
			else
			{
				if (i == e->in)
					dup2((tree->pipe)[0], STDIN_FILENO);
				e->doc = 1;
			}
		}
		if (!(e->pos))
			tree = tree->left;
		else
			tree = tree->right;
	}
}

void	open_out(t_tree *tree, t_exec *e)
{
	int	i;
	int	fd;

	i = 0;
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
				in_error(tree->str);
			if (i != e->out)
				close(fd);
			else
				dup2(fd, STDOUT_FILENO);
		}
		if (!(e->pos))
			tree = tree->left;
		else
			tree = tree->right;
	}
}

void	redirections(t_tree *tree, t_exec *e, int *fd)
{
	e->in = count_redirect(tree, e->pos, IN);
	e->out = count_redirect(tree, e->pos, OUT);
	if (e->in)
	{
		if (*fd)
			close (*fd);
		open_in(tree, e);
	}
	else
		dup2(*fd, STDIN_FILENO);
	if (e->out)
	{
		close((e->p)[1]);
		open_out(tree, e);
	}
	else
	{
		if (e->pos == e->count - 1)
			close((e->p)[1]);
		else
			dup2((e->p)[1], STDOUT_FILENO);
	}
}
