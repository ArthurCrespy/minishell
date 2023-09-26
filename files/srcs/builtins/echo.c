/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:15:32 by abinet            #+#    #+#             */
/*   Updated: 2023/09/21 15:37:40 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(t_data *data, t_exec *exec)
{
	int		index_args;
	bool	n_flag;

	(void)data;
	n_flag = false;
	if (!ft_strcmp(exec->flags[0], "-n"))
		n_flag = true;
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
