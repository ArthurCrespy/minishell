/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:59 by abinet            #+#    #+#             */
/*   Updated: 2023/10/01 21:50:57 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_unset(t_data *data, t_exec *exec)
{
	int	index;
	printf("args_nb builtins = %d\n", exec->args_nb);
	if (exec->args_nb == 0)
		printf("unset: not enough arguments\n");
	else
	{
		index = 0;
		while (index < exec->args_nb)
		{
			env_delete(data, exec->args[index]);
			index++;
		}
	}
}
