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

int	ft_env_size(t_data *data, const char *command)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	i = 0;
	size = 0;
	if (!data || !command)
		return (0);
	while (command[i] && command[i] != '\0')
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
			if (!ft_tabchr(data->env, tmp))
				size += ft_strlen(tmp) + 1;
			else
				size += ft_strlen(data->env[ft_tabchr(data->env, tmp) - 1]) - j;
			free(tmp);
		}
		i++;
	}
	size += i;
	return (size);
}

void	env_save(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	data->env = envp;
	data->return_value = 273;
}

void	replace_var(t_data *data, char *command, char *tmp, int *i, int *j)
{
	int		k;
	int 	f;
	char	*var_value;
	char	*return_value;
	char	*command_value;

	k = 0;
	f = 0;
	return_value = NULL;
	command_value = NULL;
	var_value = malloc(sizeof(char) * (ft_strlen(command) + 1));
	if (!var_value)
		ft_exit(data, MALLOC_ERROR, "replace_var malloc error");
	(*i)++;
	if (command[(*i)] == '\x1F' || command[(*i)] == '\0')
	{
		tmp[(*j)++] = command[(*i)++];
		return ;
	}
	else if (command[(*i)] == '?')
	{
		(*i)++;
		return_value = ft_itoa(data->return_value);
		while (return_value[f])
			tmp[(*j)++] = return_value[f++];
		tmp[(*j)++] = '\x1F';
		free(return_value);
		return ;
	}
	while (command[(*i)] && command[(*i)] != ' ' && command[(*i)] != '\x1F')
		var_value[k++] = command[(*i)++];
	var_value[k] = '\0';
	if (!ft_tabchr(data->env, var_value))
	{
		tmp[(*j)++] = '$';
		(*i) -= k;
		free(var_value);
		return ;
	}
	else
	{
		(*i)++;
		f = ft_strlen(var_value) + 1;
		command_value = data->env[ft_tabchr(data->env, var_value) - 1];
		while (command_value[f])
			tmp[(*j)++] = command_value[f++];
		tmp[(*j)++] = '\x1F';
		return ;
	}
}

char	*ft_env_replace(t_data *data, char *command)
{
	int		i;
	int		j;
	char	*tmp;

	if (!data || !command)
		return (NULL);
	i = 0;
	j = 0;
	tmp = ft_calloc(sizeof(char), (ft_env_size(data, command) + 1));
	if (!tmp)
		ft_exit(data, MALLOC_ERROR, "ft_env_replace malloc error");
	while (command[i])
	{
		if (command[i] == '$')
			replace_var(data, command, tmp, &i, &j);
		else
			tmp[j++] = command[i++];
	}
	tmp[j] = '\0';
	free(command);
	return (tmp);
}