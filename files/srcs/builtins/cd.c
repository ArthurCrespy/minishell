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

int	builtin_cd(t_data *data, t_exec *exec)
{
	if (exec->args_nb == 0)
	{
		if (!chdir(env_return(data, "HOME")))
		{
			env_update(data, "OLDPWD", env_return(data, "PWD"));
			env_update(data, "PWD", getcwd(NULL, 0));
		}
		else
			return (perror("cd"), 1);
	}
	else if (exec->args_nb == 1)
	{
		if (!chdir(exec->args[0]))
		{
			env_update(data, "OLDPWD", env_return(data, "PWD"));
			env_update(data, "PWD", getcwd(NULL, 0));
		}
		else
		{
			data->return_value = 1;
			return (perror("cd"), 1);
		}
	}
	else
	{
		data->return_value = 1;
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	}
	return (0);
}
