/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:27:02 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/20 19:57:44 by abinet           ###   ########.fr       */
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
	prompt_launch(&data);
	ft_free(&data);
	return (0);
}
