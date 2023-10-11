/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:03 by abinet            #+#    #+#             */
/*   Updated: 2023/10/09 15:36:24 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_cd_process(t_data *data)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	oldpwd = env_return(data, "PWD");
	if (!oldpwd)
	{
		data->return_value = 1;
		return (ft_putstr_fd("cd: PWD not set\n", 2), 1);
	}
	env_update(data, "OLDPWD", pwd);
	env_update(data, "PWD", pwd);
	free(pwd);
	return (0);
}

int	builtin_cd(t_data *data, t_exec *exec)
{
	char	*target_directory;

	if (exec->args_nb > 1)
	{
		data->return_value = 1;
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	}
	if (exec->args_nb == 0)
		target_directory = env_return(data, "HOME");
	else
		target_directory = exec->args[0];
	if (!target_directory)
	{
		data->return_value = 1;
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	}
	if (!chdir(target_directory))
		builtin_cd_process(data);
	else
	{
		data->return_value = 1;
		return (perror("cd"), 1);
	}
	return (0);
}
