/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:22:58 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/20 17:22:58 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_replace_char(t_data *data, char *command, int c)
{
	int	i;

	i = 0;
	if (!data || !command || !c)
		return (command);
	while (command[i])
	{
		if (command[i] == c)
			command[i] = '\x1F';
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_replace(t_data *data, char *command, int c)
{
	char	*tmp;

	(void) data;
	if (strchr(command, c))
	{
		tmp = ft_strplc(command, c);
		free(command);
		command = tmp;
	}
	return (command);
}
