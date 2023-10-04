/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:52:12 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/26 20:52:15 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Replace the char c by \x1F if it's not in a quote
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

// Replace the operators by \x1F
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
		if (!(ft_quotes_enclosed_simple(parsing, 0, 0, 0)
				|| ft_quotes_enclosed_double(parsing, 0, 0, 0))
			&& (parsing->command[parsing->i] == '<'
				|| parsing->command[parsing->i] == '>'
				|| parsing->command[parsing->i] == '|'))
			ft_operators_separate(parsing);
		else
			parsing->tmp[parsing->j++] = parsing->command[parsing->i++];
	}
	parsing->tmp[parsing->j] = '\0';
	free(parsing->command);
	return (parsing->tmp);
}

// Replace the quotes by \x1F
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
