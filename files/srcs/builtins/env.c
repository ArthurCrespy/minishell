/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:17:19 by abinet            #+#    #+#             */
/*   Updated: 2023/10/09 21:17:19 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(t_data *data, bool export)
{
	int		index;

	index = 0;
	while (data->env[index])
	{
		if (ft_strcmp(data->env[index], "=") == 0)
		{
			if (export == true)
			{
				ft_putstr_fd("declare -x ", STDOUT_FILENO);
				ft_putstr_fd(data->env[index], STDOUT_FILENO);
			}
			// 	ft_putstr_fd("=", STDOUT_FILENO);
			// if (export == true)
			// 	ft_putstr_fd("""", STDOUT_FILENO);
		}
		else
		{
			if (export == true)
				ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(data->env[index], STDOUT_FILENO);
		}
		if (data->env[index])
			ft_putstr_fd("\n", STDOUT_FILENO);

		index++;
	}
		// if (data->env[index])
		// 		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
