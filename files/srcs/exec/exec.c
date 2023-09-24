/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:05:43 by abinet            #+#    #+#             */
/*   Updated: 2023/09/24 21:07:11 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// verifie que le launch s'affiche bien
// boucle pour lancer chaque commande a la suite
void	exec(t_data *data)
{
	int		i;

	if (data->exec_launch == false)
	{
		printf("minishell: parse error\n");
		return ;
	}
	i = 0;
	while (data->exec[i])
	{
		data->exec[i]->id_exec = i;
		launch_exec(data, data->exec[i]);
		i++;
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
	if (set_in_and_out(data, exec, pipex))
		return (perror("raté"));
	if (set_command(data, exec))
		return (perror("raté"));
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

//definit les fdin et fdout
int	set_in_and_out(t_data *data, t_exec *exec, t_pipex *pipex)
{
	(void)data;
	(void)exec;

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
		printf("11111\n");
	}
	else if (pipex->pipefd[1])
	{
		pipex->fdout = pipex->pipefd[1];
		printf("22222\n");
	}
	else
	{
		pipex->fdout = STDOUT_FILENO;
		printf("33333\n");
	}
	printf("fdin = %d\n", pipex->fdin);
	printf("fdout = %d\n", pipex->fdout);
	return (0);
}

// definit les commandes et leur path pour execve
int	set_command(t_data *data, t_exec *exec)
{
	(void)data;
	(void)exec;
	//cmd
	//path_cmd
	return (0);
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
