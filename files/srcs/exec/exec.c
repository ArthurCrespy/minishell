/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:05:43 by abinet            #+#    #+#             */
/*   Updated: 2023/09/25 22:07:40 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// verifie que le launch s'affiche bien
// boucle pour lancer chaque commande a la suite
void	exec(t_data *data)
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
		data->exec[index]->id_exec = index;
		launch_exec(data, data->exec[index]);
		index++;
	}
}

// malloc la structure pipex qui possede les infos des redirections
// set les fdin et fdout de chaque commande
// fork
// pars dans le processus enfant
void	launch_exec(t_data *data, t_exec *exec)
{
	t_pipex	*pipex;
	//pid_t	pid;

	pipex = malloc(sizeof(t_pipex));
	exec->pipex = pipex;
	//initialiser a 0 car meme free la structure garde les valeurs de la commande precedente
	if (set_command(data, exec, pipex))
		return (perror("raté"));
	if (set_in_and_out(data, exec, pipex))
		return (perror("raté"));
	free(pipex->path_cmd);
	free(pipex->cmd);
	free(pipex);
	// pid = fork();
	// if (pid == -1)
	// 	return (perror("raté"));
	// if (pid == 0) //&& data.path_cmd1)
	// {
	// 	child(data, exec, pipex);
		//gestion erreur si exec mal passe
	// }
	//si pipe alors closepipefd[1]
	//if here_doc : unlink fichier .here_doc
}

// remplace les stdin et stdout par les fdin et fdout correspondants
// lance l'exec
void	child(t_data *data, t_exec *exec, t_pipex *pipex)
{
	(void)data;
	(void)exec;
	(void)pipex;
}


// execute les builtins qui sont appeles
void	find_cmd(t_data *data, t_exec *exec)
{
	char	*cmd;

	cmd = exec->cmd;
	if (!ft_strcmp(cmd, "exit"))
		ft_ft_exit(data, data->exec[0]);
	else if (!ft_strcmp(cmd, "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(cmd, "cd"))
		ft_cd(data, data->exec[0]);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(data, data->exec[0]);
	else if (!ft_strcmp(cmd, "echo"))
		ft_echo(data, data->exec[0]);
	else if (!ft_strcmp(cmd, "export"))
		ft_export(data, data->exec[0]);
	else if (!ft_strcmp(cmd, "env"))
		ft_env(data);
}
