/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:19:00 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/12 12:19:00 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_access(t_data *data, t_exec *exec)
{
	if (check_directory(data, exec->cmd) == 1)
		return (1);
	if (check_access(data, exec) == 1)
		return (1);
	if (check_cmd(data, exec->cmd) == 1)
		return (1);
	return (0);
}

int	ft_put_error(t_exec *exec, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(exec->cmd, 2);
	if (error)
		ft_putstr_fd(error, 2);
	else
		perror(" ");
	return (1);
}
