/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 19:58:16 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/07 14:27:25 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_case_util(char *str, int *i, int *i2)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (!str[*i])
		syntax_error();
	*i2 = *i;
	while (str[*i2] && (str[*i2] == ' ' || str[*i2] == '\t'))
		(*i2)++;
}

void	add_case_util2(int id, char *str, t_parse prs)
{
	if (id == DOC)
	{
		if (!(*(prs.ptr)))
			add_to_tree_n(id, remove_quotes(str), prs.ptr);
		else
			add_to_tree(id, remove_quotes(str), prs);
	}
	else
	{
		if (!(*(prs.ptr)))
			add_to_tree_n(id, remove_quotes(treat_dollar2(str, prs.env)),
				prs.ptr);
		else
			add_to_tree(id, remove_quotes(treat_dollar2(str, prs.env)),
				prs);
	}
}
