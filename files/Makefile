# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 14:54:39 by acrespy           #+#    #+#              #
#    Updated: 2023/05/16 15:01:53 by acrespy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := minishell

SRC_DIR     := srcs
SRCS := \
			command_parsing.c \
			command_replace.c \
			env_modify.c \
			env_replace.c \
			env_save.c \
			free.c \
			main.c \
			prompt_history.c \
			prompt_keys.c \
			prompt_launch.c \
			utils_atoi.c \
			utils_gnl.c \
			utils_split.c \
			utils_str.c \
			utils_str_mem.c \
			utils_tab.c \

SRCS := ${SRCS:%=${SRC_DIR}/%}

OBJ_DIR     := .objs
OBJS := ${SRCS:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

CC          := clang
CFLAGS      := -Wall -Wextra  -g

RM          := rm -rf
MAKEFLAGS   += --no-print-directory
DIR_DUP     = mkdir -p ${@D}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME} -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include
	${info EXECUTABLE CREATED: ${NAME}}


${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	${DIR_DUP}
	${CC} ${CFLAGS} -c -o $@ $< -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include
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