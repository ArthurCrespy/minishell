/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:16:31 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/21 16:16:31 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_istoken(char *str)
{
	if (!ft_strcmp(str, "&&"))
		return (AND);
	else if (!ft_strcmp(str, "||"))
		return (OR);
	else if (!ft_strcmp(str, ";"))
		return (SEMICOLON);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if (!ft_strcmp(str, "<"))
		return (REDIR_IN);
	else if (!ft_strcmp(str, ">"))
		return (REDIR_OUT);
	else if (!ft_strcmp(str, ">>"))
		return (REDIR_APPEND);
	else if (!ft_strcmp(str, "<<"))
		return (DELIMITER);
	else
		return (0);
}
