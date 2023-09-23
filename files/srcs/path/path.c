/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:12:03 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/19 12:12:03 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_path(t_data *data)
{
	char	*home;
	char	*path;
	char	*result;

	if (!data->env)
		return (NULL);
	home = env_return(data, "HOME");
	path = env_return(data, "PWD");
	if (home && path && ft_strncmp(home, path, ft_strlen(home)) == 0)
		result = ft_strjoin("~", path + ft_strlen(home));
	else
		result = ft_strdup(data, path);
	return (result);
}

char	*ft_device(t_data *data)
{
	int		i;
	char	*device;
	char	*session;

	if (!data->env)
		return (NULL);
	i = 6;
	device = NULL;
	session = env_return(data, "SESSION_MANAGER");
	if (session && ft_strncmp(session, "local/", 6) == 0)
	{
		device = (char *)malloc(sizeof(char) * (ft_strlen(session)));
		if (!device)
			ft_exit(data, -1, MALLOC_ERROR, "ft_device");
		while (session[i]
			&& session[i] != ',' && session[i] != ':' && session[i] != '.')
		{
			device[i - 6] = session[i];
			i++;
		}
		device[i - 6] = '\0';
	}
	else
		device = ft_strdup(data, "local");
	return (device);
}
