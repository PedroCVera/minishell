/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:28:18 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/22 18:37:44 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	nbr_backslash(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

void	bck_slsh_util(char *str, char **newstr, int *i, int *i2)
{
	if (str[*i] == '\\')
		(*i)++;
	(*newstr)[*i2] = str[*i];
	(*i2)++;
	(*i)++;
}

char	*rm_backslash(char *str, int i, int i2, char qt)
{
	char	*newstr;

	newstr = malloc(sizeof(char) * ft_strlen(str) - nbr_backslash(str) + 1);
	while (str[i])
	{
		if (str[i] && !is_diff_s(str, i, "\"'"))
		{
			qt = str[i];
			i++;
			while (str[i] && !((i < 1 || str[i - 1] != '\\') && str[i] == qt))
			{
				newstr[i2] = str[i];
				i2++;
				i++;
			}
		}
		else
			bck_slsh_util(str, &newstr, &i, &i2);
	}
	newstr[i2] = 0;
	free(str);
	return (newstr);
}
