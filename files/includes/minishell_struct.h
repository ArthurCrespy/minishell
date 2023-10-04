/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:55:15 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/01 02:23:39 by abinet           ###   ########.fr       */
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

typedef struct s_parsing
{
	char	*command;
	char	*tmp;
	int		i;
	int		j;
}				t_parsing;

typedef struct s_quotes
{
	int		j;
	int		k;
	int		opened_single;
	int		opened_double;
	int		closed_single;
	int		closed_double;
	char	*tmp;
}				t_quotes;

typedef struct s_exec
{
	int				fdin;
	int				fdout;
	char			**cmd_exec;
	char			*path_cmd;
	int				pipefd[2];
	int				id_exec;
	char			*cmd;
	char			**flags;
	char			**args;
	char			**in;
	char			**out;
	char			**out_append;
	char			**delimiter;
	int				flags_nb;
	int				args_nb;
	int				in_nb;
	int				out_nb;
	int				out_append_nb;
	int				delimiter_nb;
	int				fdin_next;
}				t_exec;

typedef struct s_data
{
	t_signal	sig;
	t_signal	sig_quit;
	t_history	*history;
	t_exec		**exec;
	int			pipes_nb;
	bool		exec_launch;
	char		**command;
	char		**env;
	int			return_value;
}				t_data;

#endif
