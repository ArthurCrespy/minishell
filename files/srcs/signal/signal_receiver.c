/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_receiver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:44:19 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/12 11:21:01 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Signal processing
void	signal_processing(int sig, siginfo_t *siginfo, void *content)
{
	(void)siginfo;
	(void)content;
	if (sig == SIGINT)
	{
		g_status = 130;
		rl_on_new_line();
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		g_status = 131;
	else if (sig == SIGTERM)
		g_status = 0;
}

void	signal_processing_child(int sig, siginfo_t *siginfo, void *content)
{
	(void)siginfo;
	(void)content;
	if (sig == SIGINT)
	{
		g_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else if (sig == SIGQUIT)
	{
		g_status = 131;
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	}
	else if (sig == SIGTERM)
		g_status = 0;
}

void	signal_processing_heredoc(int sig, siginfo_t *siginfo, void *content)
{
	(void)siginfo;
	(void)content;
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_status = 130;
	}
}

void	ft_signal_handle(t_data *data, int child)
{
	if (child == 1)
	{
		data->sig.sa_sigaction = signal_processing_child;
		sigemptyset(&data->sig.sa_mask);
		data->sig.sa_flags = SA_SIGINFO;
	}
	if (child == 2)
	{
		data->sig.sa_sigaction = signal_processing_heredoc;
		sigemptyset(&data->sig.sa_mask);
		data->sig.sa_flags = SA_SIGINFO;
	}
	sigaction(SIGINT, &data->sig, NULL);
	sigaction(SIGQUIT, &data->sig, NULL);
	sigaction(SIGTERM, &data->sig, NULL);
}

// Signal handle
// Note: SIGQUIT sa_handler is set to SIG_IGN to ignore the signal
void	signal_handle(t_data *data, int child)
{
	if (child == 0)
	{
		data->sig.sa_sigaction = signal_processing;
		data->sig_quit.sa_sigaction = signal_processing;
		sigemptyset(&data->sig.sa_mask);
		sigemptyset(&data->sig_quit.sa_mask);
		data->sig.sa_flags = SA_SIGINFO;
		data->sig_quit.sa_flags = SA_SIGINFO;
		data->sig_quit.sa_handler = SIG_IGN;
		sigaction(SIGINT, &data->sig, NULL);
		sigaction(SIGQUIT, &data->sig_quit, NULL);
		sigaction(SIGTERM, &data->sig, NULL);
	}
	else if (child == 1 || child == 2)
		ft_signal_handle(data, child);
	else if (child == 3)
	{
		sigaction(SIGINT, &data->sig_quit, NULL);
		sigaction(SIGQUIT, &data->sig_quit, NULL);
		sigaction(SIGTERM, &data->sig_quit, NULL);
	}
}
