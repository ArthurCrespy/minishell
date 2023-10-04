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

void    ft_exec_quotes_out_append(t_data *data, t_exec *exec, int i)
{
	t_quotes    *qts;

	qts = NULL;
	while (exec->out_append[i])
	{
		ft_init_quotes(data, &qts, ft_strlen(exec->out_append[i]));
		while (exec->out_append[i][qts->j])
		{
			if (exec->out_append[i][qts->j] == '\'' && !qts->opened_double)
				qts->opened_single = !qts->opened_single;
			else if (exec->out_append[i][qts->j] == '\"' && !qts->opened_single)
				qts->opened_double = !qts->opened_double;
			else if (exec->out_append[i][qts->j] == '\'' && qts->opened_double)
				qts->closed_single = !qts->closed_single;
			else if (exec->out_append[i][qts->j] == '\"' && qts->opened_single)
				qts->closed_double = !qts->closed_double;
			else
				qts->tmp[qts->k++] = exec->out_append[i][qts->j];
			qts->j++;
		}
		qts->tmp[qts->j] = '\0';
		free(exec->out_append[i]);
		exec->out_append[i] = qts->tmp;
		i++;
	}
}

void    ft_exec_quotes_delimiter(t_data *data, t_exec *exec, int i)
{
	t_quotes    *qts;

	qts = NULL;
	while (exec->delimiter[i])
	{
		ft_init_quotes(data, &qts, ft_strlen(exec->delimiter[i]));
		while (exec->delimiter[i][qts->j])
		{
			if (exec->delimiter[i][qts->j] == '\'' && !qts->opened_double)
				qts->opened_single = !qts->opened_single;
			else if (exec->delimiter[i][qts->j] == '\"' && !qts->opened_single)
				qts->opened_double = !qts->opened_double;
			else if (exec->delimiter[i][qts->j] == '\'' && qts->opened_double)
				qts->closed_single = !qts->closed_single;
			else if (exec->delimiter[i][qts->j] == '\"' && qts->opened_single)
				qts->closed_double = !qts->closed_double;
			else
				qts->tmp[qts->k++] = exec->delimiter[i][qts->j];
			qts->j++;
		}
		qts->tmp[qts->j] = '\0';
		free(exec->delimiter[i]);
		exec->delimiter[i] = qts->tmp;
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
	(*quotes)->tmp = (char *)malloc(sizeof(char) * (size + 1));
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
		ft_exec_quotes_args(data, data->exec[i], 0);
		ft_exec_quotes_flags(data, data->exec[i], 0);
		ft_exec_quotes_in(data, data->exec[i], 0);
		ft_exec_quotes_out(data, data->exec[i], 0);
		ft_exec_quotes_out_append(data, data->exec[i], 0);
		ft_exec_quotes_delimiter(data, data->exec[i], 0);
		i++;
	}
	return (data->exec);
}
