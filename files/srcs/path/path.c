/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:12:03 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/02 23:12:10 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Return the path of the current directory
char	*path_find(t_data *data)
{
	char	*home;
	char	*path;
	char	*result;

	if (!data->env)
		return (NULL);
	home = env_return(data, "HOME");
	path = env_return(data, "PWD");
	if (!path)
		path = getcwd(NULL, 0);
	if (home && path && ft_strncmp(home, path, ft_strlen(home)) == 0)
		result = ft_strjoin("~", path + ft_strlen(home));
	else if (path)
		result = ft_strdup(data, path);
	else
		result = ft_strdup(data, "local");
	return (result);
}

char	*path_find_cmd(t_data *data, t_exec *exec)
{
	unsigned int	i;
	char			**all_paths;
	char			*path;
	char			*end_path;

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
