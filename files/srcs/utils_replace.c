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

char	*ft_strplc(const char *str, int c)
{
	int		i;
	char	*result;

	i = 0;
	if (!str || !c)
		return (NULL);
	result = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			result[i] = '\x1F';
		else
			result[i] = str[i];
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
