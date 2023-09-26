/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:25 by abinet            #+#    #+#             */
/*   Updated: 2023/09/20 23:13:20 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(t_data *data)
{
	char	*working_directory;

	working_directory = env_return(data, "PWD");
	if (working_directory)
		printf("%s\n", working_directory);
}
