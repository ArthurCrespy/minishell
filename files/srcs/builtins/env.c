/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:17:19 by abinet            #+#    #+#             */
/*   Updated: 2023/09/21 18:15:56 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_data *data)
{
	int	index;

	index = 0;
	while (data->env[index])
	{
		printf("%s", data->env[index]);
		index++;
		if (data->env[index])
			printf("\n");
	}
}
