/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:03 by abinet            #+#    #+#             */
/*   Updated: 2023/09/22 17:16:35 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// cd sans options :
//					si HOME est empty alors rien
//					si HOME est defini alors HOME
// cd avec options :
//					si l'arg commence par / alors chemin absolu
//					si l'arg commence par . alors chemin relatif
//						dans le dossier actuel
//					si l'arg commence par .. alors chemin relatif,
//						dans le dossier precedent
//

// Proposition builtin cd :
/*int	ft_cd(t_data *data, t_exec *exec)
{
	if (!exec->args[0])
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
		return (printf("cd: string not in pwd: %s\n", exec->args[0]), 1);
	return (0);
}*/

int	ft_cd(t_data *data, t_exec *exec)
{
	if (exec->args_nb == 0)
	{
		if (chdir(env_return(data, "HOME")))
		{
			perror("cd");
			return (1);
		}
		else
		{
			env_update(data, "OLDPWD", env_return(data, "PWD"));
			env_update(data, "PWD", getcwd(NULL, 0));
		}
	}
	else if (exec->args_nb != 1)
	{
		printf("string not in pwd: %s", exec->args[0]);
		return (1);
	}
	else
	{
		if (chdir(exec->args[0]))
		{
			perror("cd");
			return (1);
		}
		else
		{
			env_update(data, "OLDPWD", env_return(data, "PWD"));
			env_update(data, "PWD", getcwd(NULL, 0));
		}
	}
	return (0);
}
