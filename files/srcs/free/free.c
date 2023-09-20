/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:25:56 by acrespy           #+#    #+#             */
/*   Updated: 2023/06/13 12:31:19 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_data *data, int status, char *msg)
{
	if (data)
		ft_free(data);
	if (msg)
		printf("ERROR CODE: %d - DEFAULT: %s\n", status, msg);
	exit(status);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[0])
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void ft_free_exec(t_exec **exec)
{
	int i;

	i = 0;
	while (exec[i])
	{
		if (exec[i]->cmd)
			free(exec[i]->cmd);
		if (exec[i]->flags)
			ft_free_tab(exec[i]->flags);
		if (exec[i]->args)
			ft_free_tab(exec[i]->args);
		if (exec[i]->in)
			ft_free_tab(exec[i]->in);
		if (exec[i]->out)
			ft_free_tab(exec[i]->out);
		if (exec[i]->out_append)
			ft_free_tab(exec[i]->out_append);
		if (exec[i]->delimiter)
			ft_free_tab(exec[i]->delimiter);
		free(exec[i]);
		i++;
	}
	free(exec);
}

void	ft_free(t_data *data)
{
	if (data->history)
		history_free(data);
	if (data->env)
		ft_free_tab(data->env);
}
