/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:51:12 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/19 12:51:12 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	key_read(void)
{
	char			c;
	struct termios	old_termios;
	struct termios	new_termios;

	tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios;
	new_termios.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	if (read(STDIN_FILENO, &c, 1) == -1)
		c = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
	return (c);
}

void	key_arrows(t_data *data, int key)
{
	if (key == 65 && data->history != NULL && data->history->prev != NULL)
	{
		data->history = data->history->prev;
		rl_replace_line(data->history->cmd, 1);
		rl_redisplay();
	}
	if (key == 66 && data->history != NULL && data->history->next != NULL)
	{
		data->history = data->history->next;
		rl_replace_line(data->history->cmd, 1);
		rl_redisplay();
	}
}

void	key_operators(t_data *data, int key)
{
	if (key == 10)
	{
		if (data->history != NULL)
		{
			rl_replace_line("", 1);
			rl_redisplay();
			data->history = NULL;
		}
	}
	if (key == 127)
	{
		if (data->history != NULL)
		{
			t_history *prev = data->history->prev;
			if (prev != NULL)
			{
				prev->next = data->history->next;
				if (data->history->next != NULL)
					data->history->next->prev = prev;
				free(data->history->cmd);
				free(data->history);
				data->history = prev;
			}
			else
			{
				free(data->history->cmd);
				free(data->history);
				data->history = NULL;
			}
			rl_replace_line("", 1);
			rl_redisplay();
		}
	}
}

void	key_others(t_data *data)
{
	if (data->history != NULL)
	{
		rl_replace_line("", 1);
		rl_redisplay();
		data->history = NULL;
	}
}

void	key_processing(t_data *data, int key)
{
	if (key == 27)
	{
		key = key_read();
		if (key == 91)
		{
			key = key_read();
			if (key == 65)
				key_arrows(data, 65);
			else if (key == 66)
				key_arrows(data, 66);
		}
	}
	else if (key == 10)
		key_operators(data, 10);
	else if (key == 127)
		key_operators(data, 127);
	else
		key_others(data);
}
