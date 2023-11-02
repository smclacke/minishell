# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: smclacke <smclacke@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/24 19:33:54 by smclacke      #+#    #+#                  #
#    Updated: 2023/11/02 17:46:08 by smclacke      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			= mini
DJOY			= djoyke
# SAAR			= sarah

CFLAGS			= -Wall -Wextra -g -fsanitize=address
# valgrind --leak-check=yes
# -Werror 

LFLAGS			= -L$(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline
CC				= cc
INCLUDES		= -Iinclude -Iinclude/libft/include
HEADERS			= djoyke.h shelly.h structs.h prompt.h colour.h
IFLAGS			= -I$(HOME)/.brew/Cellar/readline/8.2.1/include

HEADER_DIR		= include
HEADER			= $(addprefix $(HEADER_DIR)/, $(HEADERS))

## SARAH ##

SRCS			= main.c								\
					utils.c								\
					lexer/lexer.c						\
					lexer/lexer_utils.c					\
					lexer/token.c						\
					lexer/token_size.c					\
					lexer/token_utils.c					\
					parser/sort.c						\
					parser/sort_utils.c					\
					parser/parser.c						\
					parser/parser_utils.c				\
					expander/expand.c					\
					expander/expand_utils.c				\
					expander/quotes.c					\
					expander/quote_utils.c				\
					expander/dollar.c					\
					expander/dollar_expand.c			\
					expander/dollar_utils.c


SRC_DIR		= src
SRC		= ($(addprefix $(SRC_DIR)/, $(SRCS)) $(SRC_DJOY))


OBJ_DIR	= obj
OBJ		= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

## DJOYKE ##

SRCS_DJOY		=	builtin/echo.c						\
					builtin/cd.c 						\
					builtin/pwd.c 						\
					builtin/export.c 					\
					builtin/unset.c 					\
					builtin/env.c 						\
					builtin/builtin_utils_one.c 		\
					builtin/builtin_utils_two.c 		\
					builtin/exit.c						\
					executor/execute.c					\
					executor/execute_utils_one.c		\
					executor/execute_utils_two.c		\
					executor/make_env.c					\
					executor/utils_one.c				\
					executor/utils_two.c				\
					executor/redirect.c					\
					executor/list_utils.c 				\
					executor/print_utils.c				\
					executor/heredoc_utils.c			

DJOY_DIR		= src_djoy
SRC_DJOY		= ($(addprefix $(DJOY_DIR)/, $(SRCS_DJOY)) $(SRC))

OBJ_DJOY_DIR	= obj_djoy
OBJ_DJOY		= $(addprefix $(OBJ_DJOY_DIR)/, $(SRCS_DJOY:%.c=%.o))


all				: libft $(NAME)

djoy			: libft $(DJOY)

# saar			: libft $(SAAR)

libft			:
	@ make -C include/libft

## EXECUTABLES

$(NAME)			:	$(OBJ) $(OBJ_DJOY)
	@ $(CC) $^ $(CFLAGS) $(LFLAGS) $(IFLAGS) $(INCLUDES) include/libft/libft.a -o $(NAME)
	@ echo "${PURPLE} ---> Made!${RESET}"
	@ ./mini

# $(NAME)			:	$(OBJ)
# 	@ $(CC) $^ $(CFLAGS) $(LFLAGS) $(IFLAGS) $(INCLUDES) include/libft/libft.a -o $(NAME)
# 	@ echo "${GREEN} ---> Minishell Made!${RESET}"
# 	@ ./minishell

$(DJOY)			:	$(OBJ_DJOY) $(OBJ)
	@ $(CC) $^ $(CFLAGS) $(LFLAGS) $(IFLAGS) $(INCLUDES) include/libft/libft.a -o $(DJOY)
	@ echo "${PURPLE} ---> Djoyke Made!${RESET}"
# @ ./djoyke


## OBJECTS

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@ mkdir -p $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)/parser
	@ mkdir -p $(OBJ_DIR)/lexer
	@ mkdir -p $(OBJ_DIR)/expander
	@ mkdir -p $(OBJ_DJOY_DIR)
	@ mkdir -p $(OBJ_DJOY_DIR)/src_djoy/builtin
	@ mkdir -p $(OBJ_DJOY_DIR)/src_djoy/executor
	@ $(CC) $(CFLAGS) $(IFLAGS) $(INCLUDES) -c $< -o $@

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	@ mkdir -p $(OBJ_DIR)
# 	@ $(CC) $(CFLAGS) $(IFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DJOY_DIR)/%.o: $(DJOY_DIR)/%.c $(HEADER)
	@ mkdir -p $(OBJ_DJOY_DIR)
	@ mkdir -p $(OBJ_DJOY_DIR)/builtin
	@ mkdir -p $(OBJ_DJOY_DIR)/executor
	@ mkdir -p $(OBJ_DJOY_DIR)/src/lexer
	@ mkdir -p $(OBJ_DJOY_DIR)/src/parser
	@ mkdir -p $(OBJ_DJOY_DIR)/src/expander
	@ $(CC) $(CFLAGS) $(IFLAGS) $(INCLUDES) -c $< -o $@

## Colours ##
RESET		:= \033[0m
RED			:= \033[1;91m
GREEN		:= \033[1;92m
YELLOW		:= \033[1;93m
BLUE		:= \033[1;94m
PURPLE		:= \033[1;95m
CYAN		:= \033[1;96m
WHITE		:= \033[1;97m
BLACK		:= \033[1;90m

clean		:
	@make -C include/libft clean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DJOY_DIR)
# @rm -rf $(OBJ_SAAR_DIR)

fclean		:
	@make -C include/libft fclean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DJOY_DIR)
# @rm -rf $(OBJ_SAAR_DIR)
	@rm -rf $(NAME)
	@rm -rf $(DJOY)
# @rm -rf $(SAAR)
	@echo "${YELLOW} // Minishell fCleaned!${RESET}"

re			: fclean all

.PHONY: all clean fclean re libft sarah djoyke
