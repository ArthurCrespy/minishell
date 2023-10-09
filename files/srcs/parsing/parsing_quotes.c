/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:53:26 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/02 16:53:26 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_quotes_end(t_quotes *qts, char **input, int i)
{
	qts->tmp[qts->j] = '\0';
	if (qts->tmp[qts->j - 1] == '\0')
		qts->tmp[qts->j - 1] = '\n';
	free(input[i]);
	input[i] = qts->tmp;
	free(qts);
}

void	ft_exec_quotes_cmd(t_data *data, t_exec *exec)
{
	t_quotes	*qts;

	if (!exec->cmd)
		return ;
	ft_init_quotes(data, &qts, ft_strlen(exec->cmd));
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
	free(qts);
}

void	ft_exec_quotes_replace(t_data *data, char **input, int size)
{
	int			i;
	t_quotes	*qts;

	i = 0;
	while (i != size && input[i])
	{
		ft_init_quotes(data, &qts, ft_strlen(input[i]));
		while (input[i][qts->j])
		{
			if (input[i][qts->j] == '\'' && !qts->opened_double)
				qts->opened_single = !qts->opened_single;
			else if (input[i][qts->j] == '\"' && !qts->opened_single)
				qts->opened_double = !qts->opened_double;
			else if (input[i][qts->j] == '\'' && !qts->opened_double)
				qts->closed_single = !qts->closed_single;
			else if (input[i][qts->j] == '\"' && !qts->opened_single)
				qts->closed_double = !qts->closed_double;
			else
				qts->tmp[qts->k++] = input[i][qts->j];
			qts->j++;
		}
		ft_exec_quotes_end(qts, input, i);
		i++;
	}
}

void	ft_init_quotes(t_data *data, t_quotes **quotes, int size)
{
	(*quotes) = (t_quotes *)malloc(sizeof(t_quotes));
	if (!(*quotes))
		ft_exit(data, -1, MALLOC_ERROR, "ft_init_quotes");
	(*quotes)->j = 0;
	(*quotes)->k = 0;
	(*quotes)->opened_single = 0;
	(*quotes)->opened_double = 0;
	(*quotes)->closed_single = 0;
	(*quotes)->closed_double = 0;
	(*quotes)->tmp = (char *)calloc(sizeof(char), (size + 1));
	if (!(*quotes)->tmp)
		ft_exit(data, -1, MALLOC_ERROR, "ft_init_quotes");
}

t_exec	**ft_exec_quotes(t_data *data)
{
	int	i;

	i = 0;
	while (data->exec[i])
	{
		if (data->exec[i] == NULL)
			return (data->exec);
		ft_exec_quotes_cmd(data, data->exec[i]);
		ft_exec_quotes_replace(data, data->exec[i]->flags,
			data->exec[i]->flags_nb);
		ft_exec_quotes_replace(data, data->exec[i]->args,
			data->exec[i]->args_nb);
		ft_exec_quotes_replace(data, data->exec[i]->in,
			data->exec[i]->in_nb);
		ft_exec_quotes_replace(data, data->exec[i]->out,
			data->exec[i]->out_nb);
		ft_exec_quotes_replace(data, data->exec[i]->out_append,
			data->exec[i]->out_append_nb);
		ft_exec_quotes_replace(data, data->exec[i]->content,
			data->exec[i]->ref_nb);
		i++;
	}
	return (data->exec);
}
