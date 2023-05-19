/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:34:40 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/19 13:34:40 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_exit(t_data *data, int status, char *msg)
{
	if (data)
		ft_free(*data);
	printf("CODE: %d - ERROR: %s\n", status, msg);
	exit(status);
}

void ft_free(t_data data)
{
	history_free(&data);
}