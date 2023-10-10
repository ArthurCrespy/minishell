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
	char	*target_directory;
	char	*pwd;

	if (exec->args_nb > 1)
	{
		data->return_value = 1;
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	}
	if (exec->args_nb == 0)
		target_directory = env_return(data, "HOME");
	else
		target_directory = exec->args[0];
	if (!chdir(target_directory))
	{
		pwd = getcwd(NULL, 0);
		env_update(data, "OLDPWD", env_return(data, "PWD"));
		env_update(data, "PWD", pwd);
		free(pwd);
	}
	else
	{
		data->return_value = 1;
		return (perror("cd"), 1);
	}
	return (0);
}
