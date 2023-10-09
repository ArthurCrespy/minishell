/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:33:51 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/09 19:33:51 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_create(t_data *data)
{
	char	*tmp;

	data->env_custom = 1;
	data->env = malloc(sizeof(char *) * 4);
	if (!data->env)
		ft_exit(data, -1, MALLOC_ERROR, "env_create");
	data->env[0] = ft_strdup(data, "_=/usr/bin/env");
	tmp = getcwd(NULL, 0);
	data->env[1] = ft_strjoin("PWD=", tmp);
	data->env[2] = ft_strdup(data, "PATH=/mnt/nfs/homes/acrespy/bin:/usr/local/sbin:"
		"/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:"
		"/usr/local/games:/snap/bin");
	data->env[3] = NULL;
	free(tmp);
}