/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:22:58 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/20 17:22:58 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_char_replace(t_data *data, char *command, int c)
{
	int	i;

	i = 0;
	if (!data || !command || !c)
		return (command);
	while (command[i])
	{
		if (command[i] == c)
			command[i] = '\x1F';
		i++;
	}
	return (command);
}

void	ft_operators_separate(const char *command, char *tmp, int *i, int *j)
{
	int		count;
	char	c;

	count = 0;
	c = command[(*i)];
	while (command[(*i)] == c)
	{
		count++;
		(*i)++;
	}
	if (count == 1)
		tmp[((*j))++] = c;
	else if (count == 2)
	{
		tmp[(*j)++] = c;
		tmp[(*j)++] = c;
	}
	else
	{
		while (count--)
		{
			tmp[(*j)++] = c;
		}
	}
	tmp[(*j)++] = '\x1F';
}

char	*ft_operators_replace(t_data *data, char *command)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	len = ft_strlen(command);
	tmp = malloc(sizeof(char *) * ((len * 3) + 1));
	if (!tmp)
		ft_exit(data, MALLOC_ERROR, "ft_operators malloc error");
	while (command[i])
	{
		if (command[i] == '<' || command[i] == '>' || command[i] == '|')
		{
			tmp[j++] = '\x1F';
			ft_operators_separate(command, tmp, &i, &j);
		}
		else
			tmp[j++] = command[i++];
	}
	tmp[j] = '\0';
	free(command);
	return (tmp);
}
