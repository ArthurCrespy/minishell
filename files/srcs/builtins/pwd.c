/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:25 by abinet            #+#    #+#             */
/*   Updated: 2023/10/05 16:36:25 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(t_data *data)
{
	char	*pwd;
	char	*pwd_getcwd;

	pwd = env_return(data, "PWD");
	pwd_getcwd = NULL;
	if (!pwd)
		pwd_getcwd = getcwd(NULL, 0);
	if (!pwd_getcwd)
		return (1);
	else if (pwd)
	{
		ft_putstr_fd(pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(pwd_getcwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(pwd_getcwd);
	}
	return (0);
}
