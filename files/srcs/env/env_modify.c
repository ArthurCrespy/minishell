/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:32:06 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/22 15:54:17 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Update the value of an environment variable
void	env_update(t_data *data, char *name, char *value)
{
	int		i;
	char	*tmp;
	char	*name_tmp;
	char	*value_tmp;

	if (!name)
		return ;
	name_tmp = ft_strjoin(name, "=");
	tmp = ft_strdup(data, value);
	if (!value)
		value_tmp = ft_strdup(data, name);
	else
		value_tmp = ft_strjoin(name_tmp, tmp);
	i = ft_tabchr(data->env, name);
	if (i != 0)
	{
		free(data->env[i - 1]);
		data->env[i - 1] = ft_strdup(data, value_tmp);
	}
	free(name_tmp);
	free(value_tmp);
	free(tmp);
}

// Add a new environment variable
// Note: If the variable already exists, its value will be updated
void	env_add(t_data *data, char *name, char *value, int i)
{
	char	*name_tmp;
	char	*value_tmp;
	char	**new_env;

	if (ft_tabchr(data->env, name))
		return (env_update(data, name, value));
	name_tmp = ft_strjoin(name, "=");
	if (!value)
		value_tmp = ft_strdup(data, name);
	else
		value_tmp = ft_strjoin(name_tmp, value);
	new_env = malloc(sizeof(char *) * (ft_tablen(data->env) + 10));
	if (!new_env)
		ft_exit(data, -1, MALLOC_ERROR, "env_add");
	while (data->env[i])
	{
		new_env[i] = ft_strdup(data, data->env[i]);
		i++;
	}
	ft_free_tab(data->env);
	free(name_tmp);
	new_env[i++] = value_tmp;
	new_env[i] = NULL;
	data->env = new_env;
}

// Delete an environment variable
void	env_delete(t_data *data, char *name)
{
	int		i;
	char	**new_env;

	i = 0;
	if (!ft_tabchr(data->env, name))
		return ;
	new_env = malloc(sizeof(char *) * (ft_tablen(data->env)));
	if (!new_env)
		ft_exit(data, -1, MALLOC_ERROR, "env_delete");
	while (i != ft_tabchr(data->env, name) - 1)
	{
		new_env[i] = ft_strdup(data, data->env[i]);
		i++;
	}
	i++;
	while (data->env[i])
	{
		new_env[i - 1] = ft_strdup(data, data->env[i]);
		i++;
	}
	new_env[i - 1] = NULL;
	ft_free_tab(data->env);
	data->env = new_env;
}
