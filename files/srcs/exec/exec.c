/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:05:43 by abinet            #+#    #+#             */
/*   Updated: 2023/09/21 14:34:21 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(t_data *data)
{
	char	*cmd;

	cmd = data->exec[i]->cmd;
	if (!ft_strcmp(data->exec[i]->cmd, "pwd"))
		ft_pwd(data);
}

char	*find_cmd(t_data data, t_exec exec)
{
	if (!ft_strcmp(cmd, "exit"))
		ft_ft_exit(data, data->exec[0]);
	if (!ft_strcmp(cmd, "pwd"))
		ft_pwd(data, data->exec[0]);
	if (!ft_strcmp(cmd, "cd"))
		ft_cd(data, data->exec[0]);
	if (!ft_strcmp(cmd, "unset"))
		ft_unset(data, data->exec[0]);
	if (!ft_strcmp(cmd, "echo"))
		ft_echo(data, data->exec[0]);
	if (!ft_strcmp(cmd, "export"))
		ft_export(data, data->exec[0]);
	if (!ft_strcmp(cmd, "env"))
		ft_env(data, data->exec[0]);
}
