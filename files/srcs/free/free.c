/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:25:56 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/03 14:30:44 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_exec3(t_data *data, int i)
{
	if (data->exec[i]->content)
		ft_free_tab_little(data->exec[i]->content);
	free(data->exec[i]->content);
	if (data->exec[i]->type)
		free(data->exec[i]->type);
	free(data->exec[i]);
}

void	ft_free_exec2(t_data *data, int i)
{
	if (data->exec[i]->in)
		ft_free_tab_little(data->exec[i]->in);
	free(data->exec[i]->in);
	if (data->exec[i]->out)
		ft_free_tab_little(data->exec[i]->out);
	free(data->exec[i]->out);
	if (data->exec[i]->out_append)
		ft_free_tab_little(data->exec[i]->out_append);
	free(data->exec[i]->out_append);
	if (data->exec[i]->delimiter)
		ft_free_tab_little(data->exec[i]->delimiter);
	free(data->exec[i]->delimiter);
	ft_free_exec3(data, i);
}

void	ft_free_exec(t_data *data)
{
	int	i;

	i = 0;
	if (!data->exec)
		return ;
	while (data->exec && data->exec[i])
	{
		if (data->exec[i]->cmd)
			free(data->exec[i]->cmd);
		if (data->exec[i]->flags)
			ft_free_tab_little(data->exec[i]->flags);
		free(data->exec[i]->flags);
		if (data->exec[i]->args)
			ft_free_tab_little(data->exec[i]->args);
		free(data->exec[i]->args);
		ft_free_exec2(data, i);
		i++;
	}
	free(data->exec);
	data->exec = NULL;
}

void	ft_free(t_data *data)
{
	if (data->history)
		history_free(data);
	if (data->command)
		ft_free_tab(data->command);
	if (data->exec)
		ft_free_exec(data);
	if (data->env)
		ft_free_tab(data->env);
}
