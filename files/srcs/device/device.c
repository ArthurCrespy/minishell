/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:49:59 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/26 19:49:59 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Return the device name of the current session
// Note: The returned value must be freed
char	*device_find(t_data *data)
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
			ft_exit(data, -1, MALLOC_ERROR, "device_find");
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
