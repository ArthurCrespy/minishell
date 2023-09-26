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

#include "../../includes/minishell.h"

/*char	*ft_char_replace(t_data *data, t_parsing *parsing, int c)
{
	int	i;

	i = 0;
	if (!data || !parsing->command || !c)
		return (parsing->command);
	while (parsing->command[i])
	{
		if (parsing->command[i] == c)
			parsing->command[i] = '\x1F';
		i++;
	}
	return (parsing->command);
}*/

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

char	*ft_operators_replace(t_data *data, t_parsing *parsing)
{
	int		len;

	parsing->i = 0;
	parsing->j = 0;
	len = ft_strlen(parsing->command);
	parsing->tmp = malloc(sizeof(char *) * ((len * 3) + 1));
	if (!parsing->tmp)
		ft_exit(data, -1, MALLOC_ERROR, "ft_operators_replace");
	while (parsing->command[parsing->i])
	{
		if (parsing->command[parsing->i] == '<'
			|| parsing->command[parsing->i] == '>'
			|| parsing->command[parsing->i] == '|')
		{
			parsing->tmp[parsing->j++] = '\x1F';
			ft_operators_separate(parsing);
		}
		else
			parsing->tmp[parsing->j++] = parsing->command[parsing->i++];
	}
	parsing->tmp[parsing->j] = '\0';
	free(parsing->command);
	return (parsing->tmp);
}

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

char	*ft_quotes_replace(t_data *data, t_parsing *parsing, char c)
{
	int		len;

	parsing->i = 0;
	parsing->j = 0;
	len = ft_strlen(parsing->command);
	parsing->tmp = malloc(sizeof(char) * ((len * 2) + 1));
	if (!parsing->tmp)
		ft_exit(data, -1, MALLOC_ERROR, "ft_quotes_replace");
	while (parsing->command[parsing->i])
	{
		if (parsing->command[parsing->i] == c)
			ft_quotes_check(parsing);
		else
			parsing->tmp[parsing->j++] = parsing->command[parsing->i++];
	}
	parsing->tmp[parsing->j] = '\0';
	free(parsing->command);
	return (parsing->tmp);
}

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

char	*ft_char_replace(t_data *data, t_parsing *parsing, int c)
{
	int	i;

	i = 0;
	if (!data || !parsing->command || !c)
		return (parsing->command);
	while (parsing->command[i])
	{
		if (parsing->command[i] == c)
		{
			if (ft_quotes_closed(parsing->command + i))
				parsing->command[i] = '\x1F';
		}
		i++;
	}
	return (parsing->command);
}
