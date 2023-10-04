/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:15:32 by abinet            #+#    #+#             */
/*   Updated: 2023/10/04 15:28:26 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(t_data *data, t_exec *exec)
{
	int		index_args;
	int		index_flags;
	bool	n_flag;

	(void)data;
	n_flag = false;
	index_flags = 0;
	while (index_flags < exec->flags_nb)
	{
		if (ft_strchr(exec->flags[index_flags], 'n'))
			n_flag = true;
		index_flags++;
	}
	index_args = 0;
	while (index_args < exec->args_nb)
	{
		ft_putstr_fd(exec->args[index_args], STDOUT_FILENO);
		index_args++;
		if (index_args < exec->args_nb)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (n_flag == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
