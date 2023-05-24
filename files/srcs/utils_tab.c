/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:43:13 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/24 15:43:13 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int ft_tabchr(char **tab, const char *str)
{
	int	i;
	int	j;

	i = 0;
	if (!tab || !str)
		return (0);
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] && str[j] && tab[i][j] == str[j])
			j++;
		if (str[j] == '\0')
			return (i);
		i++;
	}
	return (0);
}