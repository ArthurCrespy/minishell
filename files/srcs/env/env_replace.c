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

int	ft_env_size(t_data *data, char *command, int i)
{
	int		j;
	int		size;
	char	*tmp;

	size = 0;
	while (command && command[i])
	{
		if (command[i] == '$')
		{
			i++;
			j = 0;
			tmp = malloc(sizeof(char) * (ft_strlen(command)));
			while (command[i] && command[i] != ' ' && command[i] != '\x1F' && command[i] != '\'')
				tmp[j++] = command[i++];
			tmp[j] = '\0';
			if (!ft_tabchr(data->env, tmp))
				size += ft_strlen(tmp) + 1;
			else
				size += ft_strlen(data->env[ft_tabchr(data->env, tmp) - 1]) - j;
			free(tmp);
		}
		else
			i++;
	}
	return (size + i);
}

void	ft_dollar_replace(t_data *data, t_parsing *parsing)
{
	int		k;
	int		f;
	char	*var_value;
	char	*command_value;

	k = 0;
	var_value = malloc(sizeof(char) * (ft_strlen(parsing->command) + 1));
	if (!var_value)
		ft_exit(data, -1, MALLOC_ERROR, "ft_dollar_replace");
	while (parsing->command[parsing->i] && parsing->command[parsing->i]
		!= ' ' && parsing->command[parsing->i] != '\x1F' && parsing->command[parsing->i] != '\'')
		var_value[k++] = parsing->command[parsing->i++];
	var_value[k] = '\0';
	if (ft_tabchr(data->env, var_value))
	{
		f = ft_strlen(var_value) + 1;
		command_value = data->env[ft_tabchr(data->env, var_value) - 1];
		while (command_value[f])
			parsing->tmp[parsing->j++] = command_value[f++];
		parsing->tmp[parsing->j++] = '\x1F';
	}
	free(var_value);
}

void	ft_dollar_check(t_data *data, t_parsing *parsing)
{
	int		k;
	char	*var_value;
	char	*return_value;

	k = 0;
	var_value = malloc(sizeof(char) * (ft_strlen(parsing->command) + 1));
	if (!var_value)
		ft_exit(data, -1, MALLOC_ERROR, "ft_dollar_check");
	parsing->i++;
	if (parsing->command[parsing->i] == '\x1F'
		|| parsing->command[parsing->i] == '\0')
		parsing->tmp[parsing->j++] = parsing->command[parsing->i - 1];
	else if (parsing->command[parsing->i] == '?')
	{
		parsing->i++;
		return_value = ft_itoa(data->return_value);
		while (return_value[k])
			parsing->tmp[parsing->j++] = return_value[k++];
		parsing->tmp[parsing->j++] = '\x1F';
	}
	else
		ft_dollar_replace(data, parsing);
	free(var_value);
}

int	ft_quotes_enclosed(t_parsing *parsing)
{
	int	i;
	int	open;

	i = parsing->i;
	open = 0;
	if (i == 0)
		return (1);
	while (parsing->command[i] && parsing->command[i] != '\0' && parsing->command[i] != '\x1F')
	{
		if (parsing->command[i] == '\"')
			open++;
		i--;
	}
	if (i == 0 || i == -1)
		return (0);
	i = parsing->i;
	while (parsing->command[i] && parsing->command[i] != '\0' && parsing->command[i] != '\x1F')
	{
		if (parsing->command[i] == '\"')
			open++;
		i++;
	}
	if (open > 0)
		return (0);
	return (1);
}

char	*ft_env_replace(t_data *data, t_parsing *parsing)
{
	parsing->i = 0;
	parsing->j = 0;
	parsing->tmp = ft_calloc(sizeof(char),
			(ft_env_size(data, parsing->command, 0) + 1));
	if (!parsing->tmp)
		ft_exit(data, -1, MALLOC_ERROR, "ft_env_replace");
	while (parsing->command[parsing->i])
	{
		if (parsing->command[parsing->i] == '$' && ft_quotes_enclosed(parsing))
			ft_dollar_check(data, parsing);
		else
			parsing->tmp[parsing->j++] = parsing->command[parsing->i++];
	}
	parsing->tmp[parsing->j] = '\0';
	free(parsing->command);
	return (parsing->tmp);
}
