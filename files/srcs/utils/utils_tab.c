/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:43:13 by acrespy           #+#    #+#             */
/*   Updated: 2023/06/13 12:14:39 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[0])
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	ft_tabslen(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!tab || !tab[0])
		return (0);
	while (tab[i])
	{
		j += ft_strlen(tab[i]);
		i++;
	}
	return (j);
}

int	ft_tabchr(char **tab, const char *str)
{
	int	i;
	int	j;

	i = 0;
	if (!tab || !str)
		return (0);
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] && tab[i][j] == str[j] && str[j])
			j++;
		if ((tab[i][j] == '=' || tab[i][j] == '\0') && str[j] == '\0')
			return (i + 1);
		i++;
	}
	return (0);
}

int	ft_tabcount(char **tab, const char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	if (!tab || !c)
		return (0);
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}
