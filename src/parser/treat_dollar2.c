/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_dollar2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:29:49 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/21 11:58:06 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_status(char *str, int i, char *val)
{
	char	*newstr;

	newstr = malloc(ft_strlen(str) - 2 + ft_strlen(val) + 1);
	get_status_utils(str, i, val, &newstr);
	free(val);
	free(str);
	return (newstr);
}

char	*get_var(char *str, int *i, char **env)
{
	int		i2;
	char	*var;

	i2 = (*i) + 1;
	if (str[i2] == '?')
	{
		return (get_status(str, *i, ft_itoa(g_status)));
		(*i)++;
	}
	while (str[i2] && is_var(str[i2]))
		i2++;
	if (i2 == (*i) + 1)
	{
		(*i)++;
		return (str);
	}
	var = add_var(str, search_var(ft_substr(str,
					(*i) + 1, i2 - 1), env), (*i) + 1, i2 - 1);
	if (str)
		free(str);
	return (var);
}

char	**treat_dollar(char **matrix, char **env)
{
	int	y;

	y = 0;
	while (matrix[y])
	{
		matrix[y] = treat_dollar2(matrix[y], env);
		y++;
	}
	return (matrix);
}

char	*treat_dollar2_util(char *str)
{
	free(str);
	return (NULL);
}

char	*treat_dollar2(char *str, char **env)
{
	int	i;
	int	qt;

	qt = 0;
	i = 0;
	while (str[i])
	{
		if (!str[i])
			return (str);
		if (str[i] && !is_diff_s(str, i, "\""))
			treat_dollar2_util2(&qt);
		if (str[i] && !is_diff_s(str, i, "'") && !qt)
			i = skip_quotes(str, i);
		if (*synt())
			return (treat_dollar2_util(str));
		if (str[i] && !is_diff_s(str, i, "$"))
			str = get_var(str, &i, env);
		else
			i++;
	}
	return (str);
}
