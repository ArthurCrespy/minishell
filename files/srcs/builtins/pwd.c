/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:25 by abinet            #+#    #+#             */
/*   Updated: 2023/09/20 22:56:46 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_data *data)
{
	char	*working_directory;
	char	*temp;
	int		len_path;

	temp = ft_path(data);
	len_path = ft_strlen(temp);
	working_directory = ft_substr(*data, ft_path(data), 1, len_path - 1);
	printf("%s\n", working_directory);
}
