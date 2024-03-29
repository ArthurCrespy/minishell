/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:59 by abinet            #+#    #+#             */
/*   Updated: 2023/10/03 14:16:18 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_unset(t_data *data, t_exec *exec)
{
	int	index;

	index = 0;
	while (index < exec->args_nb)
	{
		env_delete(data, exec->args[index]);
		index++;
	}
	return (0);
}
