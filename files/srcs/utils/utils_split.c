/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:04:30 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/19 17:22:29 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_word_size(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] && s[i] != c)
	{
		size++;
		i++;
	}
	return (size);
}

int	ft_word_count(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s && s[i] != 0x00)
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i] != 0x00)
				i++;
		}
		else
			i++;
	}
	return (word);
}

char	**ft_strsplit(t_data data, char const *s, char c)
{
	int		i;
	int		j;
	int		word;
	int		size;
	char	**strs;

	i = 0;
	j = 0;
	word = ft_word_count(s, c);
	strs = (char **)malloc((word + 1) * sizeof(char *));
	if (strs == NULL)
		ft_exit(&data, MALLOC_ERROR, "malloc failed - ORIGIN: ft_strsplit");
	while (j < word)
	{
		while (s[i] == c)
			i++;
		size = ft_word_size(s, c, i);
		strs[j] = ft_substr(data, s, i, size);
		if (!strs[j])
			ft_free_tab(strs);
		i += size;
		j++;
	}
	strs[j] = 0;
	return (strs);
}
