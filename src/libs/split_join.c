/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:08:42 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/22 16:06:57 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	num_splits(char const *str, char c)
{
	int	i;
	int	splits;

	splits = 1;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			splits++;
		i++;
	}
	return (splits);
}

char	**ft_split(char const *str, char c)
{
	char	**split;
	int		i;
	int		start;
	int		i2;

	i = 0;
	i2 = 0;
	split = malloc(sizeof(char *) * num_splits(str, c));
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] && str[i] != c && (!str[i + 1] || (str[i + 1]
					&& str[i + 1] == c)))
		{
			start = i - 1;
			while (!(str[start] && str[start] != c && (start == 0
						|| str[start - 1] == c)))
				start--;
			split[i2++] = ft_substr(str, start, i);
		}
		i++;
	}
	split[i2] = NULL;
	return (split);
}

static char	*joiner(char const *s1, char const *s2, int size1, int size2)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(size1 + size2 + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		ptr[size1 + i] = s2[i];
		i++;
	}
	ptr[size1 + i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size1;
	int		size2;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	return (joiner(s1, s2, size1, size2));
}
