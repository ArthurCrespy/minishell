/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:09:21 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/26 20:09:21 by acrespy          ###   ########.fr       */
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
	else if (error == OPEN_ERROR)
		return ("open error");
	else if (error == WAITPID_ERROR)
		return ("waitpid error");
	else if (error == TTY_ERROR)
		return ("std output/input error");
	else
		return ("unknown error");
}

// Free the data structure and exit the program
void	ft_exit(t_data *data, int code, int error, char *origin)
{
	char	*code_char;

	code_char = NULL;
	if (data)
		ft_free(data);
	if (error && origin)
	{
		code_char = ft_itoa(code);
		ft_putstr_fd("minishell exited with code ", 2);
		ft_putstr_fd(code_char, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(ft_return_error(error), 2);
		ft_putstr_fd(" at ", 2);
		ft_putstr_fd(origin, 2);
		free(code_char);
	}
	exit(code);
}
