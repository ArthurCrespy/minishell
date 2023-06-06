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

#include "../../includes/minishell.h"

int	ft_env_size(t_data *data, char *command)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	i = 0;
	size = 0;
	while (command && command[i])
	{
		if (command[i++] == '$')
		{
			j = 0;
			tmp = malloc(sizeof(char) * (ft_strlen(command)));
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
	return (size + i);
}

void	ft_dollar_replace(t_data *data, char *command, char *tmp, int *i, int *j)
{
	int		k;
	int		f;
	char	*var_value;
	char	*command_value;

	k = 0;
	var_value = malloc(sizeof(char) * (ft_strlen(command) + 1));
	if (!var_value)
		ft_exit(data, MALLOC_ERROR, "malloc failed - FROM: ft_dollar_replace");
	while (command[(*i)] && command[(*i)] != ' ' && command[(*i)] != '\x1F')
		var_value[k++] = command[(*i)++];
	var_value[k] = '\0';
	if (ft_tabchr(data->env, var_value))
	{
		(*i)++;
		f = ft_strlen(var_value) + 1;
		command_value = data->env[ft_tabchr(data->env, var_value) - 1];
		while (command_value[f])
			tmp[(*j)++] = command_value[f++];
		tmp[(*j)++] = '\x1F';
	}
	free(var_value);
}

void	ft_dollar_check(t_data *data, char *command, char *tmp, int *i, int *j)
{
	int		k;
	char	*var_value;
	char	*return_value;

	k = 0;
	var_value = malloc(sizeof(char) * (ft_strlen(command) + 1));
	if (!var_value)
		ft_exit(data, MALLOC_ERROR, "malloc failed - FROM: ft_dollar_check");
	(*i)++;
	if (command[(*i)] == '\x1F' || command[(*i)] == '\0')
		tmp[(*j)++] = command[(*i) - 1];
	else if (command[(*i)] == '?')
	{
		(*i)++;
		return_value = ft_itoa(data->return_value);
		while (return_value[k])
			tmp[(*j)++] = return_value[k++];
		tmp[(*j)++] = '\x1F';
	}
	else
		ft_dollar_replace(data, command, tmp, i, j);
	free(var_value);
}

char	*ft_env_replace(t_data *data, char *command)
{
	int		i;
	int		j;
	int		quotes;
	char	*tmp;

	i = 0;
	j = 0;
	quotes = 1;
	tmp = ft_calloc(sizeof(char), (ft_env_size(data, command) + 1));
	if (!tmp)
		ft_exit(data, MALLOC_ERROR, "(c)malloc failed - FROM: ft_env_replace");
	while (command[i])
	{
		if (command[i] == '\'')
			quotes *= -1;
		if (command[i] == '$' && quotes == 1)
			ft_dollar_check(data, command, tmp, &i, &j);
		else
			tmp[j++] = command[i++];
	}
	tmp[j] = '\0';
	free(command);
	return (tmp);
}
