/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:17:31 by abinet            #+#    #+#             */
/*   Updated: 2023/10/09 15:29:52 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_a_num(char *nb_args)
{
	int	i;

	i = 0;
	if (nb_args[i] == '-' || nb_args[i] == '+')
		i++;
	while (nb_args[i])
	{
		if (nb_args[i] < '0' || nb_args[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_exit(t_data *data, t_exec *exec)
{
	if ((exec->args_nb > 1) || (exec->args_nb && exec->flags_nb))
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		data->return_value = 1;
		return (1);
	}
	if (exec->args_nb)
	{
		if (!ft_is_a_num(exec->args[0]))
			ft_exit(data, ft_atoi(exec->args[0]) % 256, EXIT, NULL);
	}
	else if (exec->flags_nb)
	{
		if (!ft_is_a_num(exec->flags[0]))
			ft_exit(data, ft_atoi(exec->flags[0]) % 256, EXIT, NULL);
	}
	if (exec->args_nb || exec->flags_nb)
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		ft_exit(data, 2, EXIT, NULL);
	}
	ft_exit(data, 0, EXIT, NULL);
	return (1);
}
