/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:05:43 by abinet            #+#    #+#             */
/*   Updated: 2023/09/22 16:29:53 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(t_data *data)
{
	int		i;

	i = 0;
	if (data->exec_launch == false)
	{
		printf("minishell: parse error\n");
		return ;
	}
	while (data->exec[i])
	{
		find_cmd(data, data->exec[i]);
		i++;
	}
}

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

// 	else
//		ft_execve(data, data->exec[0]);
