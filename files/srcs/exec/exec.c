/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:35 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/01 02:15:19 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// verifie que le launch s'affiche bien
// boucle pour lancer chaque commande a la suite
void	exec_run(t_data *data)
{
	int		index;

	if (data->exec_launch == false)
	{
		printf("minishell: parse error\n");
		return ;
	}
	data->exec[0]->fdin_next = 0;
	index = 0;
	while (data->exec[index])
	{
		data->exec[index]->id_exec = index;
		if (exec_data_set(data, data->exec[index]) == 0)
		{
		// execve(data->exec[index]->pipex->path_cmd, data->exec[index]->pipex->cmd, data->env);

			if (data->exec[index]->id_exec != 0)
			{
				// char *line;
				// // int		fdout, fdin;
				// // fdin = data->exec[index]->pipex->fdin;
				// // fdout = data->exec[index]->pipex->fdout;
				// line = get_next_line(data->exec[index]->pipex->fdin);
				// printf("line = %s\n", line);
				// printf("fdin = %d\n", fdin);
				// printf("fdout = %d\n", fdout);
				//free(line);
			}
			// TODO: en dehors de la boucle
			if (data->pipes_nb == 0 && check_builtin(data, data->exec[index]) == 1)
			{
				exec_builtin(data, data->exec[index]);
				free(data->exec[index]->pipex);
			}
			else
				exec_launch(data, data->exec[index], data->exec[index]->pipex);
		}
		waitpid(-1, NULL, 0);
		index++;
		//printf("\n");
	}
	//sleep(2);
}

//malloc pipex
//set l'exec
int	exec_data_set(t_data *data, t_exec *exec)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (perror("pipex malloc"), 1);
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	//initialiser a 0 car meme free la structure garde les valeurs de la commande precedente
	data->exec[exec->id_exec]->pipex = pipex;
	if (exec_set_exec(data, exec, pipex) != 0)
		return (1);
	return (0);
}



// execute les builtins qui sont appeles
int	exec_builtin(t_data *data, t_exec *exec)
{
	char	*cmd;

	cmd = exec->cmd;
	if (!ft_strcmp(cmd, "exit"))
		builtin_exit(data, data->exec[0]);
	else if (!ft_strcmp(cmd, "pwd"))
		builtin_pwd(data);
	else if (!ft_strcmp(cmd, "cd"))
		builtin_cd(data, data->exec[0]);
	else if (!ft_strcmp(cmd, "unset"))
		builtin_unset(data, data->exec[0]);
	else if (!ft_strcmp(cmd, "echo"))
		builtin_echo(data, data->exec[0]);
	else if (!ft_strcmp(cmd, "export"))
		builtin_export(data, data->exec[0]);
	else if (!ft_strcmp(cmd, "env"))
		builtin_env(data);
	else
		return (1);
	return (0);
}

int	check_builtin(t_data *data, t_exec *exec)
{
	char	*cmd;

	(void)data;
	cmd = exec->cmd;
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}
