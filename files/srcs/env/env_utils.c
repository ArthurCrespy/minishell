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

// Save the environment variables
// Note: The returned value must be freed and the envp mustn't be empty
void	env_save(t_data *data, int argc, char **argv, char **envp)
{
	int		i;

	i = 0;
	(void)argc;
	(void)argv;
	if (data->env_custom)
		return ;
	if (!envp || !*envp || !envp[0])
		ft_exit(data, -1, ENV_ERROR, "env_save");
	data->env = malloc(sizeof(char *) * ft_tablen(envp) + 8);
	if (!data->env)
		ft_exit(data, -1, MALLOC_ERROR, "env_save");
	while (envp[i])
	{
		data->env[i] = ft_strdup(data, envp[i]);
		i++;
	}
	data->env[i] = NULL;
	if (ft_tabchr(data->env, "PATH") - 1 < 0)
		env_add(data, "PATH", "/mnt/nfs/homes/acrespy/bin:/usr/local/sbin:"
		"/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:"
		"/usr/local/games:/snap/bin");
	data->return_value = 0;
}

// Return the value of an environment variable
char	*env_return(t_data *data, char *name)
{
	if (!data || !name)
		return (NULL);
	if (ft_tabchr(data->env, name) - 1 < 0)
		return (NULL);
	return (data->env[ft_tabchr(data->env, name) - 1] + ft_strlen(name) + 1);
}
