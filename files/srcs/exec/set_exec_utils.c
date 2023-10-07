/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:23:27 by abinet            #+#    #+#             */
/*   Updated: 2023/10/06 21:30:54 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	if_redir_in(t_exec *exec)
{
	int	index;

	index = 0;
	while (index < exec->in_nb)
	{
		if (!ft_strcmp(exec->in[index], "here_doc"))
				exec->fdin = heredoc(exec);
		else
			exec->fdin = open(exec->in[index], O_RDWR, 644);
		if (exec->fdin == -1)
			return (1);
		if (index < exec->in_nb -1)
			close(exec->fdin);
		index++;
	}
	return (0);
}

int	if_redir_out(t_exec *exec)
{
	int	index;
	int	out_nb;
	int	out_append_nb;

	out_nb = exec->out_nb;
	out_append_nb = exec->out_append_nb;
	index = 0;
	while (out_nb + out_append_nb > 0)
	{
		if (out_append_nb)
		{
			exec->fdout = open(exec->out_append[index],
					O_CREAT | O_RDWR | O_APPEND, 0644);
			if (exec->fdout == -1)
				return (1);
			out_append_nb--;
		}
		if (out_nb)
		{
			exec->fdout = open(exec->out[index],
					O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (exec->fdout == -1)
				return (1);
			out_nb--;
		}
		if ((out_append_nb + out_nb) > 1)
			close(exec->fdout);
		index++;
	}
	return (0);
}

void	handle_open_error(void)
{
	// if (errno == ENOENT)
	// 	perror(" ");
	// if (errno == EACCES)
	// 	perror(" ");
	// if (errno == EISDIR)
}
