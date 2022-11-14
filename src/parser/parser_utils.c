/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:46:02 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/21 16:30:18 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parser_utils2(char *str, int *i)
{
	if (str[*i])
		(*i)++;
}

void	check_pipes_utils(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] && !is_diff_s(str, *i, "\"'"))
			*i = skip_quotes(str, *i);
		if (str[*i] && !is_diff_s(str, *i, "|"))
		{
			(*i)++;
			while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
				(*i)++;
			if (str[*i] && !is_diff_s(str, *i, "|"))
				syntax_error();
		}
		else
			(*i)++;
		if (*synt())
			return ;
	}
}

void	check_pipes(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && !is_diff_s(str, i, "|"))
		syntax_error();
	check_pipes_utils(str, &i);
	if (*synt())
		return ;
}

void	parser_utils3(char *str, t_tree **tree, int count, t_pipe **pipes)
{
	int	i;

	i = 0;
	while (str[i])
	{
		parser_utils(str, &i);
		if (*synt())
			return (free(str));
		if (str[i] && str[i] == '|' && str[i + 1] && str[i + 1] != '|')
		{
			tree_add_pipe(tree);
			add_pos(i, count, pipes);
			count++;
		}
		parser_utils2(str, &i);
		if (*synt())
			return (free(str));
	}
}
