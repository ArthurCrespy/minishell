/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:03 by abinet            #+#    #+#             */
/*   Updated: 2023/10/02 18:18:44 by abinet           ###   ########.fr       */
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
			return (perror("cd"), 1);
	}
	else
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	return (0);
}
