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

void	ft_quotes_check(const char *command, char *tmp, int *i, int *j)
{
	int		y;
	int		closed;
	char	c;

	y = *i + 1;
	closed = -1;
	c = command[(*i)];
	while (command[(y)] && command[(y)] != c)
		y++;
	if (command[y] == '\0' || command[y] == '\x1F')
		closed = 0;
	else if (command[y] == c)
		closed = 1;
	if (closed == 0)
		tmp[(*j)++] = c;
	if (closed == 1)
	{
		(*i)++;
		while (command[(*i)] != c)
			tmp[(*j)++] = command[(*i)++];
	}
	(*i)++;
}

char	*ft_quotes_replace(t_data *data, char *command, char c)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	len = ft_strlen(command);
	tmp = malloc(sizeof(char) * ((len * 2) + 1));
	if (!tmp)
		ft_exit(data, MALLOC_ERROR, "ft_quotes malloc error");
	while (command[i])
	{
		if (command[i] == c)
			ft_quotes_check(command, tmp, &i, &j);
		else
			tmp[j++] = command[i++];
	}
	tmp[j] = '\0';
	free(command);
	return (tmp);
}
