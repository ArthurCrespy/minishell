/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:42 by abinet            #+#    #+#             */
/*   Updated: 2023/10/04 12:36:17 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Return the variable name from the argument
// Note: The returned value must be freed

static int	check_if_a_letter(char *str)
{
	int		index;

	index = 0;
	while (str[index])
	{
		if (ft_isalpha(str[index]) == 1)
			return (0);
		index++;
	}
	return (1);
}

static int	check_name_var(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (0);
	return (1);
}

static char	*export_get_var(t_data *data, char *arg)
{
	int		index;
	char	*variable;

	index = 0;
	variable = NULL;
	if (ft_strlen(arg) == 0 || arg[0] == '=' || check_if_a_letter(arg) == 1)
	{
		ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
		return (NULL);
	}
	while (arg[index] && arg[index] != '=')
	{
		if (check_name_var(arg[index]) == 1)
		{
			ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
			return (NULL);
		}
		index++;
	}
	variable = ft_substr(data, arg, 0, index);
	return (variable);
}

int	builtin_export(t_data *data, t_exec *exec)
{
	int		index_args;
	char	*value;
	char	*variable;

	if (exec->flags_nb != 0)
		return (0);
	if (exec->args_nb == 0)
		builtin_env(data);
	index_args = 0;
	while (index_args < exec->args_nb)
	{
		variable = export_get_var(data, exec->args[index_args]);
		if (!variable)
			return (1);
		value = ft_strchr(exec->args[index_args], '=');
		if (!value)
			env_add(data, exec->args[index_args], "");
		else
			env_add(data, variable, value + 1);
		index_args++;
		free(variable);
	}
	return (0);
}
