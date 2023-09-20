/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:17:31 by abinet            #+#    #+#             */
/*   Updated: 2023/09/20 19:55:46 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_a_num(char *nb_args)
{
	int	i;

	i = 0;
	while (nb_args[i])
	{
		if (nb_args[i] < '0' || nb_args[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_ft_exit(t_data *data, t_exec *exec)
{
	(void)data;
	int	exit_value;

	if (ft_strcmp(exec->cmd, "exit"))
	{
		printf("no exit ? then no exit\n");
		return (0);
	}
	if (exec->args_nb > 1)
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	exit_value = atoi(exec->args[0]);
	if (exit_value == 1 || exit_value > 255)
	{
		printf("exit: %s: numeric argument required\n", exec->args[0]);
		exit (2);
	}
	exit(exit_value);
}
