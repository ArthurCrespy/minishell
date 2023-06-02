/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:01:59 by acrespy           #+#    #+#             */
/*   Updated: 2023/06/02 13:01:59 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_save(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	data->env = envp;
	data->return_value = 0;
}
