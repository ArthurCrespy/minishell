/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:21:16 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/19 17:24:24 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_quotes(t_data **data)
{
	int		i;
	int		j;
	int		len;
	int		quotes;
	char	*word;

	i = 0;
	quotes = 0;
	while ((*data)->command[i])
	{
		j = 0;
		len = ft_strlen((*data)->command[i]);
		word = (*data)->command[i];
		while (j < len)
		{
			if (word[j] == '\'' || word[j] == '\"')
				quotes *= -1;
			else
				word[i++] = word[j];
			j++;
		}
		word[i] = '\0';
		printf("word = %s\n", word);
	}
}

void	command_parsing(t_data *data, char *command)
{
	int	i;

	i = 0;
	command = ft_replace(data, command, ' ');
	command = ft_replace(data, command, '\t');
	data->command = ft_split(*data, command, '\x1F');
	while (data->command[i])
	{
		printf("command[%d] = %s\n", i, data->command[i]);
		i++;
	}
}
