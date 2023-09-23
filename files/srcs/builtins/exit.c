/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:17:31 by abinet            #+#    #+#             */
/*   Updated: 2023/09/21 16:27:48 by abinet           ###   ########.fr       */
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

	if (exec->args_nb > 1)
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	if (exec->args_nb == 1)
	{
		exit_value = ft_atoi(exec->args[0]);
		if (ft_is_a_num(exec->args[0]) == 1 || exit_value > 255)
		{
			printf("exit: %s: numeric argument requiered\n", exec->args[0]);
			ft_exit (data, 2, EXIT, NULL);
		}
	}
	else
		exit_value = 0;
	ft_exit(data, exit_value, EXIT, NULL);
	return (1);
}
