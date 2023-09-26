/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:27:02 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/26 20:52:58 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	g_data_access = &data;
	if (!*envp)
		ft_exit(NULL, -1, ENV_ERROR, "main");
	if (argc != 1 || argv[1])
		ft_exit(NULL, -1, ARG_ERROR, "main");
	env_save(&data, argc, argv, envp);
	signal_handle(&data);
	prompt_run(&data);
	ft_free(&data);
	return (0);
}
