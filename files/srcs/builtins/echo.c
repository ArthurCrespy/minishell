/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:15:32 by abinet            #+#    #+#             */
/*   Updated: 2023/10/01 21:29:54 by abinet           ###   ########.fr       */
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
		printf("%s", exec->args[index_args]);
		index_args++;
		if (index_args < exec->args_nb)
			printf(" ");
	}
	if (n_flag == false)
		printf("\n");
	return (0);
}
