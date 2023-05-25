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
}

char	*replace_var(t_data *data, char *var, char *command)
{
	char	*tmp = NULL;
	char	*tmp2 = NULL;
	char	*env_value = NULL;

	if (command[ft_strlen(command) - 1] != '\0')
		command[ft_strlen(command) - 1] = '\0';
	if (command[0] == '?')
	{
		tmp = ft_strjoin(var, command + 1);
		free(var);
		free(command);
		return (tmp);
	}
	else if (!ft_tabchr(data->env, var))
	{
		tmp = ft_strjoin("$", var);
		tmp = ft_strjoin(tmp, command + 1);
		free(var);
		free(command);
		return (tmp);
	}
	else
	{
		env_value = data->env[ft_tabchr(data->env, var) - 1] + strlen(var) + 1;
		env_value[ft_strlen(env_value) - 1] = '\x1F';
		tmp2 = ft_strjoin(env_value, command + 1);
		tmp = ft_strjoin(var, tmp2);
		free(var);
		free(tmp2);
		free(command);
		return (tmp);
	}
}

char	*ft_env_replace(t_data *data, char *command)
{
	int		i;
	int		j;
	char	*var;
	char	*tmp;

	if (!data || !command)
		return (NULL);
	i = 0;
	j = 0;
	var = malloc(sizeof(char) * (ft_env_size(data, command) + 2));
	tmp = malloc(sizeof(char) * (ft_env_size(data, command) + 1));

	if (!tmp)
		ft_exit(data, MALLOC_ERROR, "ft_env_replace malloc error");

	while (command[i])
	{
		if (command[i] == '$')
		{
			i++;
			j = 0;
			while (command[i] && command[i] != ' ' && command[i] != '\x1F')
				var[j++] = command[i++];
			var[j] = '\0';
			return replace_var(data, var, command + i);
		}
		else
			tmp[j++] = command[i++];
	}
	tmp[j] = '\0';
	free(command);
	return (tmp);

}