# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abinet <abinet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 14:54:39 by acrespy           #+#    #+#              #
#    Updated: 2023/10/02 18:07:44 by abinet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := minishell

SRC_DIR     := srcs
SRCS := \
			main.c \
			builtins/cd.c \
			builtins/echo.c \
			builtins/env.c \
			builtins/exit.c \
			builtins/export.c \
			builtins/pwd.c \
			builtins/unset.c \
			device/device.c \
			env/env_modify.c \
			env/env_replace.c \
			env/env_utils.c \
			exec/exec.c \
			exec/heredoc.c \
			exec/pipe.c \
			exec/set_exec.c \
			exec/exec_launch.c \
			exec/exec_builtins.c \
			exit/exit.c \
			free/free.c \
			parsing/parsing.c \
			parsing/parsing_node.c \
			parsing/parsing_quotes.c \
			parsing/parsing_quotes2.c \
			parsing/parsing_replace.c \
			parsing/parsing_replace_utils.c \
			parsing/parsing_utils.c \
			path/path.c \
			prompt/prompt_history.c \
			prompt/prompt_keys.c \
			prompt/prompt_run.c \
			prompt/prompt_utils.c \
			signal/signal_receiver.c \
			utils/utils_atoi.c \
			utils/utils_gnl.c \
			utils/utils_put.c \
			utils/utils_split.c \
			utils/utils_str.c \
			utils/utils_str_mem.c \
			utils/utils_tab.c \
			utils/utils_token.c \
			utils/utils_check.c \

SRCS := ${SRCS:%=${SRC_DIR}/%}

OBJ_DIR     := .objs
OBJS := ${SRCS:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

CC          := clang
CFLAGS      := -Wall -Wextra -Werror -g

RM          := rm -rf
MAKEFLAGS   += --no-print-directory
DIR_DUP     = mkdir -p ${@D}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME} -lreadline -L/usr/local/opt/readline/lib
	${info EXECUTABLE CREATED: ${NAME}}


${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	${DIR_DUP}
	${CC} ${CFLAGS} -c -o $@ $< -I/usr/local/opt/readline/include
	${info OBJECT CREATED: $@}

clean:
	${RM} ${OBJS} ${OBJ_DIR}
	${info REMOVED OBJECTS: ${OBJS} ${OBJ_DIR}}

fclean: clean
	${RM} ${NAME}
	${info REMOVED EXECUTABLES: ${NAME}}

re:
	${MAKE} fclean
	${MAKE} all

.PHONY: clean fclean re
.SILENT: ${OBJS} ${OBJS_CLIENT} ${NAME} ${NAME_CLIENT} clean fclean re
