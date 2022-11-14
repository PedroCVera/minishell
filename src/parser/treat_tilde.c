/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_tilde.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:29:44 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/24 13:04:19 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	treat_tilde_utils(char *str, int *i)
{
	if (str[*i] && !is_diff_s(str, *i, "\"'"))
		*i = skip_quotes(str, *i);
	if (*synt())
	{
		free(str);
		return (1);
	}
	return (0);
}

void	get_var_tilde_utils(char *str, int i, char *home, char **newstr)
{
	int		i2;
	int		i3;
	int		ii;

	i2 = 0;
	i3 = 0;
	ii = 0;
	while (str[i2 + i3])
	{
		if ((i2 + ii) == i)
		{
			while (home[ii])
			{
				(*newstr)[i2 + ii] = home[ii];
				ii++;
			}
			i3 = 1;
		}
		else
		{
			(*newstr)[i2 + ii] = str[i2 + i3];
			i2++;
		}
	}
	(*newstr)[i2 + ii] = 0;
}

char	*get_var_tilde(char *str, int i, char *home)
{
	char	*newstr;

	newstr = malloc(sizeof(char) * ft_strlen(str) - 1 + 1 + ft_strlen(home));
	get_var_tilde_utils(str, i, home, &newstr);
	free(home);
	return (newstr);
}

char	*treat_tilde(char *str, char **env)
{
	int		i;
	char	*newstr;

	i = 0;
	while (str[i])
	{
		if (treat_tilde_utils(str, &i))
			return (NULL);
		if (str[i] == '~'
			&& (i == 0 || str[i - 1] == ' ' || str[i - 1] == '\t')
			&& (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '\t'))
		{
			newstr = get_var_tilde(str, i, treat_dollar2(ft_strdup("$HOME"),
						env));
			free(str);
			str = newstr;
			i = 0;
		}
		else
			i++;
	}
	return (str);
}
