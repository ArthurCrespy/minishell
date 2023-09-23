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

char	*ft_return_error(int error)
{
	if (error == MALLOC_ERROR)
		return ("malloc error");
	else if (error == TCGETATTR_ERROR)
		return ("tcgetattr error");
	else if (error == TCSETATTR_ERROR)
		return ("tcsetattr error");
	else if (error == ENV_ERROR)
		return ("non-valid environment");
	else if (error == ARG_ERROR)
		return ("too many arguments");
	else if (error == EXECVE_ERROR)
		return ("execve error");
	else if (error == FORK_ERROR)
		return ("fork error");
	else
		return ("unknown error");
}

void	ft_exit(t_data *data, int code, int error, char *origin)
{
	if (data)
		ft_free(data);
	if (error && origin)
		printf("minishell exited with code %d: %s at %s\n", code,
			ft_return_error(error), origin);
	exit(code);
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

void	ft_free_exec(t_exec **exec)
{
	int	i;

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
	if (data->command)
		ft_free_tab(data->command);
	if (data->env)
		ft_free_tab(data->env);
}
