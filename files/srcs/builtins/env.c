/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:17:19 by abinet            #+#    #+#             */
/*   Updated: 2023/10/02 16:03:03 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(t_data *data)
{
	int		index;
	char	*pnt;

	index = 0;
	while (data->env[index])
	{
		printf("%s", data->env[index]);
		pnt = ft_strchr(data->env[index], '=');
		if (pnt)
		{
			if (*(pnt + 1) == '\0')
				printf("''");
		}
		if (data->env[index])
			printf("\n");
		index++;
	}
	return (0);
}
