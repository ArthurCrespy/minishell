/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:17:16 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/21 00:17:16 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s ", tab[i]);
		i++;
	}
}

void	print_exec(t_data *data)
{
	int	i;

	i = 0;
	printf("\n\n");
	while (data->exec[i])
	{
		printf("--- cmd: %s ---", data->exec[i]->cmd);
		printf("\n  flags: ");
		print_tab(data->exec[i]->flags);
		printf("\n  args: ");
		print_tab(data->exec[i]->args);
		printf("\n  in: ");
		print_tab(data->exec[i]->in);
		printf("\n  out: ");
		print_tab(data->exec[i]->out);
		printf("\n  out_append: ");
		print_tab(data->exec[i]->out_append);
		printf("\n  delimiter: ");
		print_tab(data->exec[i]->delimiter);
		printf("\n");
		i++;
	}
}
