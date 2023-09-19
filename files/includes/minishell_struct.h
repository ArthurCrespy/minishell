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

typedef struct s_exec
{
	int				type;
	char			*cmd;
	char			*flags;
	char			*args;
	char			*in;
	char			**out;
	int				out_pipe;
	struct s_exec	*prev;
	struct s_exec	*next;
}				t_exec;

typedef struct s_data
{
	t_signal	sig;
	t_signal	sig_quit;
	t_command	*history;
	t_exec		*exec;
	char		**command;
	char		**env;
	int			return_value;
}				t_data;

#endif
