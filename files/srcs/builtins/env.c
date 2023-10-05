/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:17:19 by abinet            #+#    #+#             */
/*   Updated: 2023/10/02 16:03:03 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(t_data *data)
{
	int		index;
	char	*pnt;

	index = 0;
	while (data->env[index])
	{
		ft_putstr_fd(data->env[index], STDOUT_FILENO);
		pnt = ft_strchr(data->env[index], '=');
		if (pnt)
		{
			if (*(pnt + 1) == '\0')
				ft_putstr_fd("''", STDOUT_FILENO);
		}
		if (data->env[index])
			ft_putstr_fd("\n", STDOUT_FILENO);
		index++;
	}
	return (0);
}
