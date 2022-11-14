/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_dollar3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:55:36 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/21 11:56:32 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	treat_dollar2_util2(int *qt)
{
	if (!(*qt))
		*qt = 1;
	else
		*qt = 0;
}

int	skip_heredoc(char *str, int i)
{
	i += 2;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && is_diff_s(str, i, " \t|&-<>"))
	{
		if (str[i] && !is_diff_s(str, i, "\"'"))
			i = skip_quotes(str, i);
		if (*synt())
			return (-1);
		i++;
	}
	return (i);
}

void	get_status_utils(char *str, int i, char *val, char **newstr)
{
	int		i2;
	int		ii;
	int		i3;

	i3 = 0;
	i2 = 0;
	ii = 0;
	while (str[i2 + i3])
	{
		if ((i2 + ii) == i)
		{
			while (val[ii])
			{
				(*newstr)[i2 + ii] = val[ii];
				ii++;
			}
			i3 = 2;
		}
		else
		{
			(*newstr)[i2 + ii] = str[i2 + i3];
			i2++;
		}
	}
	(*newstr)[i2 + ii] = 0;
}
