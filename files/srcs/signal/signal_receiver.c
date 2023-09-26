/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_receiver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:44:19 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/19 15:27:02 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Return the last signal received
// Note: set == 1 reset the signal
int	signal_status(int status, int set)
{
	static int	sig;

	if (set > 0)
		sig = -1;
	else if (status > 0)
		sig = status;
	return (sig);
}

// Signal processing
void	signal_processing(int sig, siginfo_t *siginfo, void *content)
{
	(void)siginfo;
	(void)content;
	if (sig == SIGINT)
	{
		signal_status(SIGINT, 0);
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		signal_status(SIGQUIT, 0);
	else if (sig == SIGTERM)
		signal_status(SIGTERM, 0);
}

// Signal handle
// Note: SIGQUIT sa_handler is set to SIG_IGN to ignore the signal
void	signal_handle(t_data *data)
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

/*  -- termios management --
    -- Needed when running on iMac --

	t_termios	attr_old;
	t_termios	attr_new;

	if (tcgetattr(STDIN_FILENO, &attr_old) != 0)
		ft_exit(NULL, TCGETATTR_ERROR, "tcgetattr error");
	attr_new = attr_old;
	attr_new.c_lflag |= ~ISIG;
	attr_new.c_cc[VSUSP] = 0;
	attr_new.c_lflag ^= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &attr_new) != 0)
		ft_exit(NULL, TCSETATTR_ERROR, "tcsetattr error");

    // CODE

	if (tcsetattr(STDIN_FILENO, TCSANOW, &attr_old) != 0)
		ft_exit(NULL, TCSETATTR_ERROR, "tcsetattr error");*/
