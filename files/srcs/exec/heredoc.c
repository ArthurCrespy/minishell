/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:29:28 by abinet            #+#    #+#             */
/*   Updated: 2023/09/26 20:51:45 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc(t_exec *exec)
{
	char	*line;
	size_t	len;
	int		fd_temp;

	fd_temp = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1)
	{
		printf("heredoc> ");
		line = get_next_line(STDIN_FILENO);
		len = ft_strlen(line);
		line[len - 1] = '\0';
		if (ft_strncmp(line, exec->delimiter[0], len) == 0)
			break ;
		ft_putstr_fd(line, fd_temp);
		free(line);
	}
	close(fd_temp);
	return (fd_temp);
}
