/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:35 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/28 17:53:14 by abinet           ###   ########.fr       */
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
		exec_data_set(data, data->exec[index]);
		//exec_builtin(data, data->exec[index]);
		//execve(data->exec[index]->pipex->path_cmd, data->exec[index]->pipex->cmd, data->env);
		exec_launch(data, data->exec[index], data->exec[index]->pipex);
		waitpid(-1, NULL, 0);
		index++;
	}
	//sleep(2);
}

//malloc pipex
//set l'exec
void	exec_data_set(t_data *data, t_exec *exec)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (perror("exec_data_set failed"));
	//initialiser a 0 car meme free la structure garde les valeurs de la commande precedente
	data->exec[exec->id_exec]->pipex = pipex;
	exec_set_exec(data, exec, pipex);
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
