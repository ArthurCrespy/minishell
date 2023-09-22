/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:17:19 by abinet            #+#    #+#             */
/*   Updated: 2023/09/22 16:20:11 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_data *data)
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
		index++;
		if (data->env[index])
			printf("\n");
	}
}
