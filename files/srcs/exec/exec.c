/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:35 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/01 21:53:51 by abinet           ###   ########.fr       */
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
			// TODO: en dehors de la boucle
			if (data->pipes_nb == 0 && index == 0 && check_builtin(data, data->exec[index]) == 1)
			{
				exec_builtin(data, data->exec[index]);
			}
			else
				exec_launch(data, data->exec[index]);
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
	if (exec_set_exec(data, exec) != 0)
		return (1);
	return (0);
}



// execute les builtins qui sont appeles
int	exec_builtin(t_data *data, t_exec *exec)
{
	char	*cmd;

	cmd = exec->cmd;
	if (!ft_strcmp(cmd, "exit"))
		builtin_exit(data, data->exec[exec->id_exec]);
	else if (!ft_strcmp(cmd, "pwd"))
		builtin_pwd(data);
	else if (!ft_strcmp(cmd, "cd"))
		builtin_cd(data, data->exec[exec->id_exec]);
	else if (!ft_strcmp(cmd, "unset"))
		builtin_unset(data, data->exec[exec->id_exec]);
	else if (!ft_strcmp(cmd, "echo"))
		builtin_echo(data, data->exec[exec->id_exec]);
	else if (!ft_strcmp(cmd, "export"))
		builtin_export(data, data->exec[exec->id_exec]);
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
