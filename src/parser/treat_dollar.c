/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:28:26 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/07 20:08:22 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_var(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int	till_eq(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

char	*search_var(char *var, char **env)
{
	int	i;
	int	len;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, till_eq(env[i])) && !var[till_eq(env[i])])
			break ;
		i++;
	}
	len = ft_strlen(var);
	if (var)
		free(var);
	if (!env[i])
		return (NULL);
	return (ft_strdup(env[i] + len + 1));
}

void	add_var_util(t_add_var v)
{
	v.i = 0;
	v.i2 = 0;
	while ((v.str)[v.i])
	{
		if ((v.str)[v.i] && v.i >= v.start - 1 && v.i <= v.end)
		{
			v.i = -1;
			if (v.var)
			{
				while (v.var[++v.i])
				{
					(*(v.newstr))[v.i2] = v.var[v.i];
					v.i2++;
				}
			}
			v.i = v.end + 1;
		}
		if ((v.str)[v.i] && (v.i < v.start || v.i > v.end))
			(*(v.newstr))[v.i2] = (v.str)[v.i];
		if ((v.str)[v.i])
			v.i++;
		v.i2++;
	}
}

char	*add_var(char *str, char *var, int start, int end)
{
	char		*newstr;
	t_add_var	v;

	if (var)
		newstr = malloc(ft_strlen(str) - (end - start + 2)
				+ ft_strlen(var) + 1);
	else
		newstr = malloc(ft_strlen(str) - (end - start + 2) + 1);
	v.str = str;
	v.var = var;
	v.newstr = &newstr;
	v.start = start;
	v.end = end;
	add_var_util(v);
	if (var)
		newstr[ft_strlen(str) - (end - start + 2) + ft_strlen(var)] = 0;
	else
		newstr[ft_strlen(str) - (end - start + 2)] = 0;
	if (var)
		free(var);
	return (newstr);
}
