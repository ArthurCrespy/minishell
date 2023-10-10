/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:06:28 by abinet            #+#    #+#             */
/*   Updated: 2023/10/02 18:06:51 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_is_minishell(t_data *data, char *cmd)
{
	char	*str;

	if (!cmd || ft_strlen(cmd) < 9)
		return (0);
	str = ft_substr(data, cmd, ft_strlen(cmd) - 9, 9);
	if (ft_strncmp(str, "minishell", 9) == 0)
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}
