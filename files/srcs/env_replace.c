/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:48:15 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/23 10:48:15 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Definitely need improvement
int	ft_env_size(t_data *data, const char *command)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	i = 0;
	size = 0;
	while (command[i])
	{
		if (command[i++] == '$')
		{
			j = 0;
			tmp = malloc(sizeof(char) * (ft_strlen(command)));
			if (!tmp)
				ft_exit(data, MALLOC_ERROR, "ft_env_size malloc error");
			while (command[i] && command[i] != ' ' && command[i] != '\x1F')
				tmp[j++] = command[i++];
			tmp[j] = '\0';
			size += (ft_strlen(data->env[ft_tabchr(data->env, tmp)]) + j) + 3;
			free(tmp);
		}
		i++;
	}
	return (size);
}

void	env_save(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	data->env = envp;
}

char	*ft_env_replace(t_data *data, char *command)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_env_size(data, command) + 1));
	if (!tmp)
		ft_exit(data, MALLOC_ERROR, "ft_env_replace malloc error");
	while (command[i])
	{
		if (command[i] == '$')
		{
			else
			{
				while (command[i] && command[i] != ' ' && command[i] != '\x1F')
					tmp[j++] = command[i++];
			}
		}
		else
			tmp[j++] = command[i++];
	}
	tmp[j] = '\0';
	free(command);
	return (tmp);
}
