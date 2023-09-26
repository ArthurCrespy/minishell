/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:12:03 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/25 21:40:21 by abinet           ###   ########.fr       */
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

char	*find_path_cmd(t_data *data, t_exec *exec, t_pipex *pipex)
{
	unsigned int	i;
	char			**all_paths;
	char			*path;
	char			*end_path;

	(void)pipex;
	all_paths = ft_strsplit(data, env_return(data, "PATH"), ':');
	if (!all_paths)
		return (0);
	i = 0;
	end_path = ft_strjoin("/", exec->cmd);
	while (all_paths[i])
	{
		path = ft_strjoin(all_paths[i], end_path);
		if (access(path, F_OK) == 0)
			return (free(end_path), ft_free_tab(all_paths), path);
		free(path);
		i++;
	}
	free(end_path);
	ft_free_tab(all_paths);
	return (0);
}
