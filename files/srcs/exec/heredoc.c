/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:29:28 by abinet            #+#    #+#             */
/*   Updated: 2023/10/10 00:49:38 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_while(t_exec *exec, int fd_temp)
{
	size_t	len;
	char	*input;

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
}

int	heredoc(t_exec *exec)
{
	int		fd_temp;

	fd_temp = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_temp == -1)
		return (-1);
	heredoc_while(exec, fd_temp);
	close(fd_temp);
	exec->fdin = open(".heredoc", O_RDONLY, 0777);
	return (0);
}
