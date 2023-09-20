/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:17:31 by abinet            #+#    #+#             */
/*   Updated: 2023/09/20 23:07:07 by abinet           ###   ########.fr       */
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
	int	exit_value;

	(void)data;
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
	printf("%p\n\n", exec->args[0]);
	if (exec->args[0])
	{
		exit_value = ft_atoi(exec->args[0]);
		if (ft_is_a_num(exec->args[0]) == 1 || exit_value > 255)
		{
			printf("exit: %s: numeric argument requiered\n", exec->args[0]);
			exit (2);
		}
	}
	else
		exit_value = 0;
	exit(exit_value);
}
