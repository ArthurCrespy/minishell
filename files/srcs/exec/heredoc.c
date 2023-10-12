/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:29:28 by abinet            #+#    #+#             */
/*   Updated: 2023/10/12 13:16:02 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_while(t_data *data, t_exec *exec, int fd_temp)
{
	size_t	len;
	char	*input;

	signal_handle(data, 2);
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (ft_strcmp(input, exec->delimiter[exec->delimiter_num])
			&& ft_strcmp(input, ""))
		{
			len = ft_strlen(input);
			input[len] = '\0';
			ft_putstr_fd(input, fd_temp);
			ft_putstr_fd("\n", fd_temp);
		}
		else if (!ft_strcmp(input, exec->delimiter[exec->delimiter_num]))
		{
			free(input);
			break ;
		}
		free(input);
	}
	signal_handle(data, 1);
}

int	heredoc(t_data *data, t_exec *exec)
{
	int		fd_temp;
	int		fd_stdin;

	fd_temp = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd_temp == -1)
		return (1);
	fd_stdin = dup(STDIN_FILENO);
	heredoc_while(data, exec, fd_temp);
	if (g_status == 130)
	{
		dup2(fd_stdin, STDIN_FILENO);
		close(fd_stdin);
		close(fd_temp);
		unlink(".heredoc");
		return (1);
	}
	else
		close(fd_stdin);
	close(fd_temp);
	exec->fdin = open(".heredoc", O_RDONLY, 0777);
	return (0);
}
