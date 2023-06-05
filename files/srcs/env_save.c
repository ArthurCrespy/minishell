/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:01:59 by acrespy           #+#    #+#             */
/*   Updated: 2023/06/02 13:01:59 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_save(t_data *data, int argc, char **argv, char **envp)
{
	int		i;
	char	**env;

	i = 0;
	(void)argc;
	(void)argv;
	if (!envp || !envp[0])
		ft_exit(data, ENV_ERROR, "minishell need an valid working environment");
	env = malloc(sizeof(char *) * ft_tablen(envp));
	if (!env)
		ft_exit(data, MALLOC_ERROR, "env_save malloc error");
	while (envp[i])
	{
		data->env[i] = ft_strdup(*data, envp[i]);
		i++;
	}
	data->return_value = 0;
}
