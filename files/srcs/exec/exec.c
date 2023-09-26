/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:35 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/26 20:51:41 by acrespy          ###   ########.fr       */
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
	index = 0;
	while (data->exec[index])
	{
		exec_builtin(data, data->exec[index]);
		data->exec[index]->id_exec = index;
		exec_data_set(data, data->exec[index]);
		index++;
	}
}

//malloc pipex
//set l'exec
void	exec_data_set(t_data *data, t_exec *exec)
{
	t_pipex	*pipex;
	//pid_t	pid;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (perror("exec_data_set failed"));
	//initialiser a 0 car meme free la structure garde les valeurs de la commande precedente
	exec->pipex = pipex;
	exec_set_exec(data, exec, pipex);
	//execve(pipex->path_cmd, pipex->cmd, data->env);
	free(pipex->path_cmd);
	free(pipex->cmd);
	free(pipex);
	// pid = fork();
	// if (pid == -1)
	// 	return (perror("raté"));
	// if (pid == 0) //&& data.path_cmd1)
	// {
	// 	exec_child(data, exec, pipex);
		//gestion erreur si exec mal passe
	// }
	//si pipe alors closepipefd[1]
	//if here_doc : unlink fichier .heredoc
}

// remplace les stdin et stdout par les fdin et fdout correspondants
// lance l'exec
void	exec_child(t_data *data, t_exec *exec, t_pipex *pipex)
{
	(void)data;
	(void)exec;
	(void)pipex;
}

// execute les builtins qui sont appeles
void	exec_builtin(t_data *data, t_exec *exec)
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
}
