# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: smclacke <smclacke@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/24 19:33:54 by smclacke      #+#    #+#                  #
#    Updated: 2023/06/24 19:49:54 by smclacke      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
DJOYKE		= djoy
SARAH		= saar

CFLAGS		= -Wall -Wextra -Werror
CC			= cc
INCLUDES	= -Iinclude Iinclude/libft_sarah/src

SRCS_DJOY	= main_djoy.c				\
				executor/executor.c		\
				expander/expander.c		\
				lexer/lexer.c			\
				parser/parser.c

SRCS_SAAR	= main_saar.c

SRC_DIR		= src
SRC_DJOY	= $(addprefix $(SRC_DIR)/, $(SRCS_DJOY))
SRC_SAAR	= $(addprefix $(SRC_DIR)/, $(SRCS_SAAR))

OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRCS_DJOY:%.c=%.o)) $(addprefix $(OBJ_DIR)/, $(SRCS_SAAR:%.c=%.o))
