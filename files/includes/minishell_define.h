/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:53:38 by acrespy           #+#    #+#             */
/*   Updated: 2023/06/06 14:53:38 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# define EXIT 0
# define MALLOC_ERROR 1
# define TCGETATTR_ERROR 2
# define TCSETATTR_ERROR 3
# define ENV_ERROR 4
# define ARG_ERROR 5
# define EXECVE_ERROR 6
# define FORK_ERROR 7
# define OPEN_ERROR 8
# define WAITPID_ERROR 9

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define CMD 0
# define SEMICOLON 1
# define AND 2
# define OR 3
# define PIPE 4
# define REDIR_IN 5
# define REDIR_OUT 6
# define REDIR_APPEND 7
# define DELIMITER 8

# define BUFFER_SIZE 1024

#endif
