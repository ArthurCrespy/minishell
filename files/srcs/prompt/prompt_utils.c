/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:52:39 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/26 20:52:42 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Return useful informations about the device to the prompt
char	*prompt_device_info(t_data *data)
{
	char	*tmp;
	char	*path;
	char	*device;
	char	*user;
	char	*result;

	path = path_find(data);
	device = device_find(data);
	user = env_return(data, "USER");
	if (!user)
		user = "user";
	result = ft_strjoin(user, "@");
	tmp = ft_strjoin(result, device);
	free(result);
	result = ft_strjoin(tmp, ":");
	free(tmp);
	tmp = ft_strjoin(result, path);
	free(result);
	result = ft_strjoin(tmp, "> ");
	return (free(tmp), free(path), free(device), result);
}
