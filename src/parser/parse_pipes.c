/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:02:20 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/22 16:07:00 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
-Arguments:
[tree] = address of the binary tree

-Funtion:
	Adds a new pipe module to the binary tree
*/
void	tree_add_pipe(t_tree **tree)
{
	t_tree	*ptr;
	t_tree	*pipe;

	ptr = *tree;
	pipe = malloc(sizeof(*pipe));
	pipe->id = PIPE;
	pipe->left = NULL;
	pipe->right = NULL;
	pipe->up = NULL;
	pipe->str = NULL;
	if (!ptr)
	{
		*tree = pipe ;
		return ;
	}
	while (ptr->up)
		ptr = ptr->up;
	ptr->up = pipe;
	pipe->left = ptr;
}

/*
-Arguments:
[str] = the input recieved by [read_line]
[pipes] = a linked list with every pipe, its position and its number

-Function:
	Separates the input by each pipe found into a matrix
*/
char	**separate_pipes(char *str, t_pipe *pipes)
{
	int		i;
	char	**matrix;
	t_pipe	*ptr;

	ptr = pipes;
	if (!pipes)
		return (NULL);
	while (ptr->next)
		ptr = ptr->next;
	matrix = malloc(sizeof(char *) * (ptr->count + 3));
	i = 0;
	while (pipes)
	{
		matrix[pipes->count] = ft_substr(str, i, pipes->pos - 1);
		i = pipes->pos + 1;
		if (!pipes->next)
		{
			matrix[pipes->count + 1] = ft_substr(str, i, ft_strlen(str) - 1);
			matrix[pipes->count + 2] = 0;
		}
		pipes = pipes->next;
	}
	return (matrix);
}

/*
-Arguments:
[pos] = the position the pipe was found int the input
[count] = the number of the pipe
[pipes] = the linked list the pipe is going to get added

-Function:
	Adds a new pipe to the pipe linked list with its respective 
	position and count
*/
void	add_pos(int pos, int count, t_pipe **pipes)
{
	t_pipe	*new;
	t_pipe	*ptr;

	ptr = *pipes;
	new = malloc(sizeof(*new));
	new->pos = pos;
	new->next = NULL;
	new->count = count;
	if (!ptr)
	{
		*pipes = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}
