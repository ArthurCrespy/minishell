/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:03 by abinet            #+#    #+#             */
/*   Updated: 2023/10/09 17:44:58 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_arg_0(t_data *data)
{
	if (!chdir(env_return(data, "HOME")))
	{
		env_update(data, "OLDPWD", env_return(data, "PWD"));
		env_update(data, "PWD", getcwd(NULL, 0));
	}
	else
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static int	cd_arg(t_data *data, t_exec *exec)
{
	if (!chdir(exec->args[0]))
	{
		env_update(data, "OLDPWD", env_return(data, "PWD"));
		env_update(data, "PWD", getcwd(NULL, 0));
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(exec->args[0], 2);
		perror(" ");
		data->return_value = 1;
		return (1);
	}
	return (0);
}

int	builtin_cd(t_data *data, t_exec *exec)
{
	if (exec->args_nb == 0)
	{
		if (cd_arg_0(data) == 1)
			return (1);
	}
	else if (exec->args_nb == 1)
	{
		if (cd_arg(data, exec) == 1)
			return (1);
	}
	else
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		data->return_value = 1;
		return (1);
	}
	return (0);
}
