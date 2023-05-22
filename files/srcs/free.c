/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:25:56 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/19 17:26:33 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_data *data, int status, char *msg)
{
	if (data)
		ft_free(*data);
	printf("CODE: %d - ERROR: %s\n", status, msg);
	exit(status);
}

void	ft_free(t_data data)
{
	if (data.history)
		history_free(&data);
	if (data.command)
		ft_free_tab(data.command);
}
