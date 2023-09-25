/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:40:47 by abinet            #+#    #+#             */
/*   Updated: 2023/09/25 21:41:49 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//definit les fdin et fdout
int	set_in_and_out(t_data *data, t_exec *exec, t_pipex *pipex)
{
	//fdin : stdin
	//		 fichier
	//		 pipefd[0]
	//		 here_doc
	if (exec->delimiter_nb)
	{
		here_doc(exec);
		pipex->fdin = open(".here_doc", O_RDONLY);
		// ne marche pas parfaitement notamment :
		// tous les "heredoc>" sont a la fin au lieu d'etre en debut de ligne
	}
	else if (exec->in_nb == 1)
		pipex->fdin = open(exec->in[0], O_RDONLY);
	else if (exec->id_exec == 0)
		pipex->fdin = STDIN_FILENO;
	else
		pipex->fdin = data->exec[exec->id_exec - 1]->pipex->pipefd[0];

	//fdout : stdout
	//		  fichier
	//		  pipefd[1]
	if (exec->out_nb)
	{
		pipex->fdout = open(exec->out[0], O_RDONLY);
		//printf("11111\n");
	}
	else if (pipex->pipefd[1])
	{
		pipex->fdout = pipex->pipefd[1];
		//printf("22222\n");
	}
	else
	{
		pipex->fdout = STDOUT_FILENO;
		//printf("33333\n");
	}
	//printf("fdin = %d\n", pipex->fdin);
	//printf("fdout = %d\n", pipex->fdout);
	return (0);
}



// definit les commandes et leur path pour execve
int	set_command(t_data *data, t_exec *exec, t_pipex *pipex)
{
	int	len;
	int	index;

	(void)data;
	(void)exec;

	//cmd
	len = 1 + exec->args_nb + exec->flags_nb;
	index = 0;
	pipex->cmd = malloc(sizeof(char *) * (len + 1));
	if (!pipex->cmd)
		return (1);
	while (index < len)
	{
		pipex->cmd[index] = data->command[index];
		index++;
	}
	pipex->cmd[index] = NULL;

	//path_cmd
	if (ft_strchr(exec->cmd, '/'))
		pipex->path_cmd = exec->cmd;
	else
		pipex->path_cmd = find_path_cmd(data, exec, pipex);
	return (0);
}
