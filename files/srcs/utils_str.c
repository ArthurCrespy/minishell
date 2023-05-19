/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:40:39 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/19 12:40:39 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		if (s1[i] <= s2[i] || s1[i] >= s2[i])
			return (s1[i] - s2[i]);
	}
	return (s1[i] - s2[i]);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (i <= (int)ft_strlen(str))
	{
		result[i] = str[i];
		i++;
	}
	return (result);
}