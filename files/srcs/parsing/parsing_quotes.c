/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:53:26 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/02 16:53:26 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_quotes_cmd(t_data *data, t_exec *exec)
{
	t_quotes	*qts;

	qts = NULL;
	ft_init_quotes(data, &qts, ft_strlen(exec->cmd));
	if (!exec->cmd)
		return ;
	while (exec->cmd[qts->j])
	{
		if (exec->cmd[qts->j] == '\'' && !qts->opened_double)
			qts->opened_single = !qts->opened_single;
		else if (exec->cmd[qts->j] == '\"' && !qts->opened_single)
			qts->opened_double = !qts->opened_double;
		else if (exec->cmd[qts->j] == '\'' && qts->opened_double)
			qts->closed_single = !qts->closed_single;
		else if (exec->cmd[qts->j] == '\"' && qts->opened_single)
			qts->closed_double = !qts->closed_double;
		else
			qts->tmp[qts->k++] = exec->cmd[qts->j];
		qts->j++;
	}
	qts->tmp[qts->j] = '\0';
	free(exec->cmd);
	exec->cmd = qts->tmp;
}

void	ft_exec_quotes_args(t_data *data, t_exec *exec, int i)
{
	t_quotes	*qts;

	qts = NULL;
	while (exec->args[i])
	{
		ft_init_quotes(data, &qts, ft_strlen(exec->args[i]));
		while (exec->args[i][qts->j])
		{
			if (exec->args[i][qts->j] == '\'' && !qts->opened_double)
				qts->opened_single = !qts->opened_single;
			else if (exec->args[i][qts->j] == '\"' && !qts->opened_single)
				qts->opened_double = !qts->opened_double;
			else if (exec->args[i][qts->j] == '\'' && qts->opened_double)
				qts->closed_single = !qts->closed_single;
			else if (exec->args[i][qts->j] == '\"' && qts->opened_single)
				qts->closed_double = !qts->closed_double;
			else
				qts->tmp[qts->k++] = exec->args[i][qts->j];
			qts->j++;
		}
		qts->tmp[qts->j] = '\0';
		free(exec->args[i]);
		exec->args[i] = qts->tmp;
		i++;
	}
}

void	ft_exec_quotes_flags(t_data *data, t_exec *exec, int i)
{
	t_quotes	*qts;

	qts = NULL;
	while (exec->flags[i])
	{
		ft_init_quotes(data, &qts, ft_strlen(exec->flags[i]));
		while (exec->flags[i][qts->j])
		{
			if (exec->flags[i][qts->j] == '\'' && !qts->opened_double)
				qts->opened_single = !qts->opened_single;
			else if (exec->flags[i][qts->j] == '\"' && !qts->opened_single)
				qts->opened_double = !qts->opened_double;
			else if (exec->flags[i][qts->j] == '\'' && qts->opened_double)
				qts->closed_single = !qts->closed_single;
			else if (exec->flags[i][qts->j] == '\"' && qts->opened_single)
				qts->closed_double = !qts->closed_double;
			else
				qts->tmp[qts->k++] = exec->flags[i][qts->j];
			qts->j++;
		}
		qts->tmp[qts->j] = '\0';
		free(exec->flags[i]);
		exec->flags[i] = qts->tmp;
		i++;
	}
}

void	ft_exec_quotes_in(t_data *data, t_exec *exec, int i)
{
	t_quotes	*qts;

	qts = NULL;
	while (exec->in[i])
	{
		ft_init_quotes(data, &qts, ft_strlen(exec->in[i]));
		while (exec->in[i][qts->j])
		{
			if (exec->in[i][qts->j] == '\'' && !qts->opened_double)
				qts->opened_single = !qts->opened_single;
			else if (exec->in[i][qts->j] == '\"' && !qts->opened_single)
				qts->opened_double = !qts->opened_double;
			else if (exec->in[i][qts->j] == '\'' && qts->opened_double)
				qts->closed_single = !qts->closed_single;
			else if (exec->in[i][qts->j] == '\"' && qts->opened_single)
				qts->closed_double = !qts->closed_double;
			else
				qts->tmp[qts->k++] = exec->in[i][qts->j];
			qts->j++;
		}
		qts->tmp[qts->j] = '\0';
		free(exec->in[i]);
		exec->in[i] = qts->tmp;
		i++;
	}
}

void	ft_exec_quotes_out(t_data *data, t_exec *exec, int i)
{
	t_quotes	*qts;

	qts = NULL;
	while (exec->out[i])
	{
		ft_init_quotes(data, &qts, ft_strlen(exec->out[i]));
		while (exec->out[i][qts->j])
		{
			if (exec->out[i][qts->j] == '\'' && !qts->opened_double)
				qts->opened_single = !qts->opened_single;
			else if (exec->out[i][qts->j] == '\"' && !qts->opened_single)
				qts->opened_double = !qts->opened_double;
			else if (exec->out[i][qts->j] == '\'' && qts->opened_double)
				qts->closed_single = !qts->closed_single;
			else if (exec->out[i][qts->j] == '\"' && qts->opened_single)
				qts->closed_double = !qts->closed_double;
			else
				qts->tmp[qts->k++] = exec->out[i][qts->j];
			qts->j++;
		}
		qts->tmp[qts->j] = '\0';
		free(exec->out[i]);
		exec->out[i] = qts->tmp;
		i++;
	}
}
