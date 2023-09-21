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
	if (!str)
		return (NULL);
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

char	*ft_substr(t_data data, char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	length;

	i = 0;
	length = 0;
	if ((int)start > ft_strlen(s))
		return (ft_strdup(data, ""));
	while (s[start + length] && length < len)
		length++;
	str = malloc((length + 1) * sizeof(char));
	if (!str)
		ft_exit(&data, MALLOC_ERROR, "malloc failed - ORIGIN: ft_substr");
	while (s[start + i] && i < length)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
