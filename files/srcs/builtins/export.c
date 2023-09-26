/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:42 by abinet            #+#    #+#             */
/*   Updated: 2023/09/22 17:17:42 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Return the variable name from the argument
// Note: The returned value must be freed
static char	*export_get_var(t_data *data, char *arg)
{
	int		index;
	char	*variable;

	index = 0;
	while (arg[index] && arg[index] != '=')
		index++;
	variable = ft_substr(data, arg, 0, index);
	return (variable);
}

int	builtin_export(t_data *data, t_exec *exec)
{
	int		index_args;
	char	*value;
	char	*variable;

	if (exec->args_nb == 0)
		builtin_env(data);
	index_args = 0;
	while (index_args < exec->args_nb)
	{
		value = ft_strchr(exec->args[index_args], '=');
		variable = export_get_var(data, exec->args[index_args]);
		if (!value)
			env_add(data, exec->args[index_args], "");
		else
			env_add(data, variable, value + 1);
		index_args++;
		free(variable);
	}
	return (0);
}
