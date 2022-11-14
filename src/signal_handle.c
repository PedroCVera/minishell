/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:28:35 by pedro             #+#    #+#             */
/*   Updated: 2022/10/21 11:52:15 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_signals(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		g_status = 130;
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	handle_signals_heredoc(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		unlink(".heredoc_tmp");
		exit(130);
	}
}

void	prep_act(struct sigaction *act, char si_mode)
{
	ft_memset(act, '\0', sizeof(*act));
	act->sa_flags = SA_SIGINFO;
	sigemptyset(&act->sa_mask);
	if (si_mode == SI_IGN)
		(act->sa_handler) = SIG_IGN;
	else if (si_mode == SI_HDOC)
		(act->sa_sigaction) = handle_signals_heredoc;
	else if (si_mode == SI_RLINE)
		(act->sa_sigaction) = handle_signals;
	else if (si_mode == SI_DFL)
		(act->sa_handler) = SIG_DFL;
	else
		return ;
}

void	call_sigact(char act_choice)
{
	struct sigaction	act;

	prep_act(&act, act_choice);
	if (sigaction(SIGQUIT, &act, NULL) == -1
		|| sigaction(SIGINT, &act, NULL) == -1)
	{
		exit(1);
	}
}

void	ignore_slashl(void)
{
	sigset_t	set;

	sigemptyset(&set);
	sigaddset(&set, SIGQUIT);
	sigprocmask(SIG_BLOCK, &set, NULL);
}
