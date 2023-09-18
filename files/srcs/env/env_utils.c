/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:01:59 by acrespy           #+#    #+#             */
/*   Updated: 2023/06/13 11:40:00 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_save(t_data *data, int argc, char **argv, char **envp)
{
	int		i;

	i = 0;
	(void)argc;
	(void)argv;
	if (!envp || !*envp || !envp[0])
		ft_exit(data, ENV_ERROR, "non-valid environment - ORIGIN: env_save");
	data->env = malloc(sizeof(char *) * ft_tablen(envp) + 8);
	if (!data->env)
		ft_exit(data, MALLOC_ERROR, "malloc failed - ORIGIN: env_save");
	while (envp[i])
	{
		data->env[i] = ft_strdup(*data, envp[i]);
		i++;
	}
	data->env[i] = NULL;
	data->return_value = 0;
}

char    *env_return(t_data *data, char *name)
{
	if (!data || !name)
		return (NULL);
	if (ft_tabchr(data->env, name) - 1 < 0)
		return (NULL);
	return (data->env[ft_tabchr(data->env, name) - 1] + ft_strlen(name) + 1);
}
