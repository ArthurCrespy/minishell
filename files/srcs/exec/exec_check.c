/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:16:22 by abinet            #+#    #+#             */
/*   Updated: 2023/10/09 17:39:51 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cmd(t_data *data, char *cmd)
{
	int	fd;

	fd = open(cmd, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		data->return_value = 126;
		return (1);
	}
	else
		close(fd);
	return (0);
}

int	check_directory(t_data *data, char *cmd)
{
	int	fd;

	fd = open(cmd, O_DIRECTORY);
	if (fd >= 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		data->return_value = 126;
		return (1);
	}
	else
		return (0);
}

int	check_access(t_data *data, t_exec *exec)
{
	if (access(exec->cmd, F_OK) == 0)
		exec->cmd_path = ft_strdup(data, exec->cmd);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(exec->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->return_value = 127;
		return (1);
	}
	return (0);
}
