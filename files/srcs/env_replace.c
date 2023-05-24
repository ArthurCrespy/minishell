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

size_t	ft_env_replace_size(t_data *data, char *command)
{
	(void)data;
	(void)command;
	return (1000);
}

void	env_save(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	data->env = envp;
}

void	ft_env_check(const char *command, char *tmp, int *i, int *j)
{
	int	check;

	check = 0;
	(*i)++;
	while (command[(*i)] && command[(*i)] != ' ' && command[(*i)] != '$'
		&& command[(*i)] != '\'' && command[(*i)] != '\"')
	{
		tmp[(*j)++] = command[(*i)++];
		check = 1;
	}
}

char	*ft_env_replace(t_data *data, char *command)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char *) * ft_env_replace_size(data, command));
	if (!tmp)
		ft_exit(data, MALLOC_ERROR, "ft_env_replace malloc error");
	while (command[i])
	{
		if (command[i] == '$')
			ft_env_check(command, tmp, &i, &j);
		else
			tmp[j++] = command[i++];
		printf("tmp[%d] = %c\n", j - 1, tmp[j - 1]);
	}
	tmp[j] = '\0';
	free(command);
	return (tmp);
}
