/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:32:06 by acrespy           #+#    #+#             */
/*   Updated: 2023/06/02 18:32:10 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_update(t_data *data, char *name, char *value)
{
	int		i;
	char	*name_tmp;
	char	*value_tmp;

	if (!name || !value)
		return ;
	i = ft_tabchr(data->env, name);
	name_tmp = ft_strjoin(name, "=");
	value_tmp = ft_strjoin(name_tmp, value);
	if (i != 0)
	{
		free(data->env[i - 1]);
		data->env[i - 1] = value_tmp;
		free(name_tmp);
	}
}

void	env_add(t_data *data, char *name, char *value)
{
	int		i;
	char	*name_tmp;
	char	*value_tmp;
	char	**new_env;

	i = 0;
	if (ft_tabchr(data->env, name))
		return (env_update(data, name, value));
	name_tmp = ft_strjoin(name, "=");
	value_tmp = ft_strjoin(name_tmp, value);
	new_env = malloc(sizeof(char *) * (ft_tablen(data->env) + 2));
	if (!new_env)
		ft_exit(data, MALLOC_ERROR, "malloc failed - FROM: env_add");
	while (data->env[i])
	{
		new_env[i] = ft_strdup(*data, data->env[i]);
		i++;
	}
	ft_free_tab(data->env);
	free(name_tmp);
	new_env[i] = value_tmp;
	data->env = new_env;
}

void	env_delete(t_data *data, char *name)
{
	int		i;
	char	**new_env;

	i = 0;
	if (!ft_tabchr(data->env, name))
		return ;
	new_env = malloc(sizeof(char *) * (ft_tablen(data->env)));
	if (!new_env)
		ft_exit(data, MALLOC_ERROR, "malloc failed - FROM: env_delete");
	while (i != ft_tabchr(data->env, name) - 1)
	{
		new_env[i] = ft_strdup(*data, data->env[i]);
		i++;
	}
	i++;
	while (data->env[i])
	{
		new_env[i - 1] = ft_strdup(*data, data->env[i]);
		i++;
	}
	ft_free_tab(data->env);
	data->env = new_env;
}