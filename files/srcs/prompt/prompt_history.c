/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:50:55 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/19 12:50:55 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	history_add(t_data *data, char *cmd)
{
	t_history	*ptr;
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	if (!new)
		ft_exit(data, MALLOC_ERROR, "malloc failed - ORIGIN: history_add");
	new->cmd = ft_strdup(*data, cmd);
	new->prev = NULL;
	new->next = NULL;
	if (!data->history)
		data->history = new;
	else
	{
		ptr = data->history;
		while (ptr->next != NULL)
			ptr = ptr->next;
		new->prev = ptr;
		ptr->next = new;
	}
	add_history(cmd);
	free(new->cmd);
	free(new);
}

void	history_free(t_data *data)
{
	t_history	*ptr;
	t_history	*tmp;

	ptr = data->history;
	while (ptr != NULL)
	{
		tmp = ptr;
		if (ptr->next == NULL)
			break ;
		ptr = ptr->next;
		free(tmp);
	}
	data->history = NULL;
}
