/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:40:39 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/19 17:26:19 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen(const char *str)
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

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (!c)
		return (str + ft_strlen(str));
	while (s[i] && s[i] != (char)c)
		i++;
	if (i == ft_strlen(s))
		return (NULL);
	else
		return (str + i);
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
		ft_exit(&data, MALLOC_ERROR, "ft_substr malloc error");
	while (s[start + i] && i < length)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i_s1;
	int		i_s2;
	char	*result;

	i_s1 = 0;
	i_s2 = 0;
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (!result)
		return (NULL);
	if (s1)
	{
		while (s1[i_s1])
		{
			result[i_s1] = s1[i_s1];
			i_s1++;
		}
	}
	while (s2[i_s2])
	{
		result[i_s1 + i_s2] = s2[i_s2];
		i_s2++;
	}
	result[i_s1 + i_s2] = '\0';
	return (result);
}
