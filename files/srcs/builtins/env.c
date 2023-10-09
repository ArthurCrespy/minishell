/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:17:19 by abinet            #+#    #+#             */
/*   Updated: 2023/10/09 21:30:22 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(t_data *data)
{
	int		index;

	index = 0;
	while (data->env[index])
	{
		if (ft_strchr(data->env[index], '=') != NULL)
		{
			ft_putstr_fd(data->env[index], STDOUT_FILENO);
			if (data->env[index])
				ft_putstr_fd("\n", STDOUT_FILENO);
		}
		index++;
	}
	return (0);
}
