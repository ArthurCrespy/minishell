/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:27:02 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/09 21:26:46 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	g_status = -1;
	data.history = NULL;
	data.exec = NULL;
	data.command = NULL;
	data.env_custom = 0;
	if (!*envp)
		env_create(&data);
	// if (isatty(0) != 1 || isatty(2) != 1)
	// 	ft_exit(NULL, -1, TTY_ERROR, "main");
	if (argc != 1 || argv[1])
		ft_exit(NULL, -1, ARG_ERROR, "main");
	env_save(&data, argc, argv, envp);
	signal_handle(&data, 0);
	prompt_run(&data);
	ft_free(&data);
	return (0);
}
