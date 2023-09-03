# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: smclacke <smclacke@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/24 19:33:54 by smclacke      #+#    #+#                  #
#    Updated: 2023/09/03 21:02:49 by smclacke      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
DJOY			= djoyke
SAAR			= sarah
MICRO_SHELL		= micro

CFLAGS			= -Wall -Wextra -g -fsanitize=address

# -Werror 
LFLAGS			= -L$(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline
CC				= cc
INCLUDES		= -Iinclude -Iinclude/libft/include
IFLAGS			= -I$(HOME)/.brew/Cellar/readline/8.2.1/include

# ifdef DEBUG
# CFLAGS += -g
# endif

# ifdef
# CFLAGS += -fsanitize=address,undefined
# endif

## MINISHELL ##

SRCS		=	main.c			\
				executor.c		\
				expander.c		\
				lexer.c			\
				parser.c

SRC_DIR			= mini_src
SRC				= $(addprefix $(SRC_DIR)/, $(SRCS))

OBJ_DIR			= obj
OBJ				= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

## DJOYKE ##

SRCS_DJOY		=	main_djoy.c			\
					env_list.c			\
					utils.c				\
					builtin/ft_echo.c	\
					builtin/ft_cd.c 	\
					builtin/ft_pwd.c 	\
					builtin/ft_export.c \
					builtin/ft_unset.c 	\
					builtin/ft_env.c 	\
					test/pipes_forks.c	\
					test/fake_input.c	
					

DJOY_DIR		= src_djoy
SRC_DJOY		= $(addprefix $(DJOY_DIR)/, $(SRCS_DJOY))

OBJ_DJOY_DIR	= obj_djoy
OBJ_DJOY		= $(addprefix $(OBJ_DJOY_DIR)/, $(SRCS_DJOY:%.c=%.o))

## SARAH ##

SRCS_SAAR		= main_saar.c					\
					lexer/lexer.c				\
					lexer/lexer_quotes.c		\
					lexer/lexer_quote_utils.c	\
					lexer/lexer_utils.c			\
					parser/parser.c				\
					parser/meta_split.c			\
					parser/parser_utils.c		\
					parser/parser_quotes.c		\
					utils/error.c

SAAR_DIR		= src_saar
SRC_SAAR		= $(addprefix $(SAAR_DIR)/, $(SRCS_SAAR))

OBJ_SAAR_DIR	= obj_saar
OBJ_SAAR		= $(addprefix $(OBJ_SAAR_DIR)/, $(SRCS_SAAR:%.c=%.o))

## MICRO_SHELL ##

SRCS_MICRO		= main.c					\
					lexer/lexer.c			\
					lexer/lexer_utils.c		\
					parser/parser.c			\
					parser/parser_quotes.c	\
					parser/parser_utils.c	\
					builtin/micro_cd.c		\
					builtin/micro_echo.c	\
					builtin/micro_env.c		\
					builtin/micro_export.c	\
					builtin/micro_pwd.c		\
					builtin/micro_unset.c	\
					executor/micro_env.c 	\
					executor/micro_execute.c	\
					executor/micro_utils.c	\
					expander/micro_expand.c 
					

MICRO_DIR		= micro_shell
SRC_MICRO		= $(addprefix $(MICRO_DIR)/, $(SRCS_MICRO))

OBJ_MICRO_DIR	= obj_micro
OBJ_MICRO		= $(addprefix $(OBJ_MICRO_DIR)/, $(SRCS_MICRO:%.c=%.o))

all				: libft $(NAME)

djoy			: libft $(DJOY)

saar			: libft $(SAAR)

libft			:
	@ make -C include/libft


## EXECUTABLES

$(NAME)			:	$(OBJ)
	@ $(CC) $^ $(CFLAGS) $(LFLAGS) $(IFLAGS) $(INCLUDES) include/libft/libft.a -o $(NAME)
	@ echo "${GREEN} ---> Minishell Made!${RESET}"
	@ ./minishell

$(DJOY)			:	$(OBJ_DJOY)
	@ $(CC) $^ $(CFLAGS) $(LFLAGS) $(IFLAGS) $(INCLUDES) include/libft/libft.a -o $(DJOY)
	@ echo "${PURPLE} ---> Djoyke Made!${RESET}"
	@ ./djoyke

$(SAAR)			:	$(OBJ_SAAR)
	@ $(CC) $^ $(CFLAGS) $(LFLAGS) $(IFLAGS) $(INCLUDES) include/libft/libft.a -o $(SAAR)
	@ echo "${PURPLE} ---> Sarah Made!${RESET}"
	@ ./sarah

$(MICRO_SHELL)	:	$(OBJ_MICRO)
	@ $(CC) $^ $(CFLAGS) $(LFLAGS) $(IFLAGS) $(INCLUDES) include/libft/libft.a -o $(MICRO_SHELL)
	@ echo "${WHITE}our micro mini shell${RESET}"
	# @ ./micro

## OBJECTS

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $(OBJ_DIR)
	@ $(CC) $(CFLAGS) $(IFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DJOY_DIR)/%.o: $(DJOY_DIR)/%.c
	@ mkdir -p $(OBJ_DJOY_DIR)
	@ mkdir -p $(OBJ_DJOY_DIR)/builtin
	@ mkdir -p $(OBJ_DJOY_DIR)/test
	@ $(CC) $(CFLAGS) $(IFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_SAAR_DIR)/%.o: $(SAAR_DIR)/%.c
	@ mkdir -p $(OBJ_SAAR_DIR)
	@ mkdir -p $(OBJ_SAAR_DIR)/parser
	@ mkdir -p $(OBJ_SAAR_DIR)/lexer
	@ mkdir -p $(OBJ_SAAR_DIR)/utils
	@ $(CC) $(CFLAGS) $(IFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_MICRO_DIR)/%.o: $(MICRO_DIR)/%.c
	@ mkdir -p $(OBJ_MICRO_DIR)
	@ mkdir -p $(OBJ_MICRO_DIR)/parser
	@ mkdir -p $(OBJ_MICRO_DIR)/lexer
	@ mkdir -p $(OBJ_MICRO_DIR)/expander
	@ mkdir -p $(OBJ_MICRO_DIR)/executor
	@ mkdir -p $(OBJ_MICRO_DIR)/builtin
	@ $(CC) $(CFLAGS) $(IFLAGS) $(INCLUDES) -c $< -o $@

# debug:
# 	$(MAKE) DEBUG=1
# .PHONY: debug

# rebug: fclean debug
# .PHONY: rebug

# fsan:
# 	$(MAKE) DEBUG=1 FSAN=1
# .PHONY: fsan

# resan: fclean fsan
# .PHONY: resan


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
	@rm -rf $(OBJ_SAAR_DIR)
	@rm -rf $(OBJ_MICRO_DIR)

fclean		:
	@make -C include/libft fclean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DJOY_DIR)
	@rm -rf $(OBJ_SAAR_DIR)
	@rm -rf $(NAME)
	@rm -rf $(DJOY)
	@rm -rf $(SAAR)
	@rm -rf $(MICRO_SHELL)
	@echo "${YELLOW} // Minishell fCleaned!${RESET}"

re			: fclean all

.PHONY: all clean fclean re libft sarah djoyke micro_shell
