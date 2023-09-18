/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:33:33 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/23 11:33:33 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(t_data data, char *str)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!result)
		ft_exit(&data, MALLOC_ERROR, "malloc failed - ORIGIN: ft_strdup");
	while (i <= (int)ft_strlen(str))
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*result;

	i = 0;
	if ((size != 0 && nmemb != 0) && ((nmemb * size) / size != nmemb))
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (NULL);
	result = malloc(nmemb * size);
	if (!result)
		return (NULL);
	while (i < nmemb * size)
	{
		result[i] = '\0';
		i++;
	}
	return (result);
}
