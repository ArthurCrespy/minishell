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
	char	*working_directory;

	working_directory = env_return(data, "PWD");
	if (!working_directory)
		working_directory = getcwd(NULL, 0);
	if (!working_directory)
		return (1);
	else
	{
		ft_putstr_fd(working_directory, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (0);
}
