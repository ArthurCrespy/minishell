/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:16:03 by abinet            #+#    #+#             */
/*   Updated: 2023/09/21 15:59:57 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// cd sans options :
//					si HOME est empty alors rien
//					si HOME est defini alors HOME
// cd avec options :
//					si l'arg commence par / alors 
//					si l'arg commence par .
//
//

int	ft_cd(t_data *data, t_exec *exec)
{
	(void)data;
	(void)exec;

	return (0);
}





	// char	*working_directory;

	// working_directory = env_return(data, "PWD");
