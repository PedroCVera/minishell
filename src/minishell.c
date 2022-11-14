/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:25:48 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/08 15:24:07 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_status = 0;

// line = readline("\e[1;32mralves-g&pcoimbra:\e[1;34mshell> \e[0m");

void	rl_crl_d(char *line)
{
	if (!line)
	{
		printf("\nexit\n");
		rl_clear_history();
		exit(g_status);
	}
}

int	rl_enter(char *line)
{
	if (!ft_strlen(line))
	{
		free(line);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_tree	*tree;
	char	*line;
	char	**env2;

	(void)ac;
	(void)av;
	*synt() = 0;
	tree = NULL;
	env2 = get_env(env);
	ignore_slashl();
	while (1)
	{
		call_sigact(SI_RLINE);
		line = readline("ralves-g&pcoimbra:shell> ");
		call_sigact(SI_IGN);
		if (line && ft_strlen(line))
			add_history(line);
		rl_crl_d(line);
		if (rl_enter(line))
			continue ;
		parser(line, &tree, 0, &env2);
		free_tree(free_tree_utils(&tree));
		*synt() = 0;
	}
}
