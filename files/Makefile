# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abinet <abinet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 14:54:39 by acrespy           #+#    #+#              #
#    Updated: 2023/09/25 22:06:01 by abinet           ###   ########.fr        #
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
			command/command_parsing.c \
			command/command_parsing_utils.c \
			command/command_processing.c \
			command/command_replace.c \
			env/env_modify.c \
			env/env_replace.c \
			env/env_utils.c \
			exec/exec.c \
			free/free.c \
			path/path.c \
			print/print.c \
			prompt/prompt_history.c \
			prompt/prompt_keys.c \
			prompt/prompt_launch.c \
			signal/signal_receiver.c \
			utils/utils_atoi.c \
			utils/utils_gnl.c \
			utils/utils_split.c \
			utils/utils_str.c \
			utils/utils_str_mem.c \
			utils/utils_tab.c \
			utils/utils_token.c \
			utils/utils_put.c \
			exec/here_doc.c \
			exec/set_exec.c


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
