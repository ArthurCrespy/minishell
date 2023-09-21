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

typedef struct s_history
{
	char				*cmd;
	struct s_history	*prev;
	struct s_history	*next;
}				t_history;

typedef struct s_command
{
	char			*cmd;
	int				flags_nb;
	char			**flags;
	int				args_nb;
	char			**args;
	int				in_nb;
	char			**in;
	int				out_nb;
	char			**out;
	int				out_append_nb;
	char			**out_append;
	int				delimiter_nb;
	char			**delimiter;
}				t_exec;

typedef struct s_data
{
	t_signal	sig;
	t_signal	sig_quit;
	t_history	*history;
	t_exec		**exec;
	char		**command;
	char		**env;
	int			return_value;
}				t_data;

#endif
