/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:42 by abinet            #+#    #+#             */
/*   Updated: 2023/10/09 23:58:25 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Return the variable name from the argument
// Note: The returned value must be freed

static int	print_export(t_data *data)
{
	int		index;
	char	*tmp;

	index = 0;
	while (data->env[index])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(data->env[index], STDOUT_FILENO);
		if (ft_strchr(data->env[index], '=') != NULL)
		{
			tmp = ft_strchr(data->env[index], '=');
			if (tmp != NULL && (*(tmp + 1) == '\0' || *(tmp + 1) == '\n'))
				ft_putstr_fd("\"\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		index++;
	}
	return (0);
}

static int	check_char_var(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (0);
	return (1);
}

// static int	check_name_var(char *str)
// {
// 	int	index;

// 	index = 0;
// 	while (str[index] && str[index] != '=')
// 	{
// 		if (check_char_var(str[index]) == 1)
// 			return (1);
// 		index++;
// 	}
// 	return (0);
// }

static char	*get_value(t_data *data, char *str)
{
	int		index;
	char	*value;

	if (!str)
		return (NULL);
	index = 1;
	while (str[index])
	{
		if (check_char_var(str[index]) == 1)
			break ;
		index++;
	}
	value = ft_substr(data, str, 0, index);
	return (value);
}

static char	*export_get_var(t_data *data, char *arg)
{
	int		index;

	index = 0;
	if (ft_strlen(arg) == 0 || arg[0] == '=' || ft_isalpha(arg[0]) == 0)
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		data->return_value = 1;
		return (NULL);
	}
	while (arg[index] && arg[index] != '=')
	{
		if (check_char_var(arg[index]) == 1)
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			data->return_value = 1;
			return (NULL);
		}
		index++;
	}
	return (ft_substr(data, arg, 0, index));
}

int	builtin_export(t_data *data, t_exec *exec)
{
	int		index_args;
	char	*value;
	char	*variable;

	if (exec->args_nb == 0)
		print_export(data);
	index_args = 0;
	while (index_args < exec->args_nb)
	{
		variable = export_get_var(data, exec->args[index_args]);
		if (!variable)
			return (1);
		value = get_value(data, ft_strchr(exec->args[index_args], '='));
		if (!value)
			env_add(data, variable, NULL, 0);
		else if (*(value + 1) == '\0' || *(value + 1) == '\n')
			env_add(data, variable, "", 0);
		else
			env_add(data, variable, value + 1, 0);
		index_args++;
		free(value);
		free(variable);
	}
	return (0);
}
