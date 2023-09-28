/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_replace_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:52:06 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/26 20:52:08 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Separate the operators by \x1F
void	ft_operators_separate(t_parsing *parsing)
{
	int		count;
	char	c;

	count = 0;
	c = parsing->command[parsing->i];
	while (parsing->command[parsing->i] == c)
	{
		count++;
		parsing->i++;
	}
	if (count == 1)
		parsing->tmp[(parsing->j)++] = c;
	else if (count == 2)
	{
		parsing->tmp[parsing->j++] = c;
		parsing->tmp[parsing->j++] = c;
	}
	else
	{
		while (count--)
			parsing->tmp[parsing->j++] = c;
	}
	parsing->tmp[parsing->j++] = '\x1F';
}

// Check if the quotes are closed
void	ft_quotes_check(t_parsing *parsing)
{
	int		y;
	int		closed;
	char	c;

	y = parsing->i + 1;
	closed = -1;
	c = parsing->command[parsing->i];
	while (parsing->command[(y)] && parsing->command[(y)] != c)
		y++;
	if (parsing->command[y] == '\0' || parsing->command[y] == '\x1F')
		closed = 0;
	else if (parsing->command[y] == c)
		closed = 1;
	if (closed == 0)
		parsing->tmp[parsing->j++] = c;
	if (closed == 1)
	{
		parsing->i++;
		while (parsing->command[parsing->i] != c)
			parsing->tmp[parsing->j++] = parsing->command[parsing->i++];
	}
	parsing->i++;
}

// Check if the quotes are closed
int	ft_quotes_closed(const char *str)
{
	int	i;
	int	opened_simple;
	int	opened_double;

	i = 0;
	opened_simple = 0;
	opened_double = 0;
	while (str[i] != '\0' && str[i] != '\x1F')
	{
		if (str[i] == '\'' && opened_double == 0)
			opened_simple = !opened_simple;
		if (str[i] == '\"' && opened_simple == 0)
			opened_double = !opened_double;
		i++;
	}
	return (opened_simple == 0 && opened_double == 0);
}

// Check if the word is enclosed by double quotes
int	ft_quotes_enclosed(t_parsing *parsing, int open, int i)
{
	i = parsing->i;
	if (i == 0)
		return (1);
	while (parsing->command[i] && parsing->command[i] != '\0'
		&& parsing->command[i] != '\x1F')
	{
		if (parsing->command[i] == '\"')
			open++;
		i--;
	}
	if (i == 0 || i == -1)
		return (0);
	i = parsing->i;
	while (parsing->command[i] && parsing->command[i] != '\0'
		&& parsing->command[i] != '\x1F')
	{
		if (parsing->command[i] == '\"')
			open++;
		i++;
	}
	if (open > 0)
		return (0);
	return (1);
}
