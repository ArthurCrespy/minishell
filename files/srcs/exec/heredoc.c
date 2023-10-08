/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:29:28 by abinet            #+#    #+#             */
/*   Updated: 2023/10/09 00:52:11 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc(t_exec *exec)
{
	int		fd_temp;
	char	*input;
	size_t	len;

	fd_temp = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_temp == -1)
		return (-1);
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			break ;
		if (ft_strcmp(input, exec->delimiter[0]) && ft_strcmp(input, ""))
		{
			len = ft_strlen(input);
			input[len] = '\0';
			ft_putstr_fd(input, fd_temp);
			ft_putstr_fd("\n", fd_temp);
		}
		else if (!ft_strcmp(input, exec->delimiter[0]))
		{
			free(input);
			break ;
		}
		free(input);
	}
	close(fd_temp);
	return (fd_temp);
}
