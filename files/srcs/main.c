/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:27:02 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/27 16:36:24 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	g_data_access = &data;
	data.history = NULL;
	data.exec = NULL;
	data.command = NULL;
	if (!*envp)
		ft_exit(NULL, -1, ENV_ERROR, "main");
	if (argc != 1 || argv[1])
		ft_exit(NULL, -1, ARG_ERROR, "main");
	env_save(&data, argc, argv, envp);
	signal_handle(&data);
	prompt_run(&data);
	//ft_free(&data);
	printf("\nfinish\n");
	return (0);
}
