/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:55:15 by acrespy           #+#    #+#             */
/*   Updated: 2023/06/06 14:55:20 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct s_command
{
	char				*cmd;
	struct s_command	*prev;
	struct s_command	*next;
}				t_command;

typedef struct s_data
{
	t_signal	sig;
	t_command	*history;
	char		**command;
	char		**env;
	int			return_value;
	int			prompt_status;
}				t_data;

#endif
