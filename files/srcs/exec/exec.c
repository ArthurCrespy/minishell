/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:05:43 by abinet            #+#    #+#             */
/*   Updated: 2023/09/20 23:06:06 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(t_data *data)
{
	int	i;

	i = 0;
	printf("on est la\n\n");
	if (!ft_strcmp(data->exec[i]->cmd, "exit"))
		ft_ft_exit(data, data->exec[i]);
	if (!ft_strcmp(data->exec[i]->cmd, "pwd"))
		ft_pwd(data);
}
