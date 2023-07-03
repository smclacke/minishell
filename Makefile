# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: smclacke <smclacke@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/24 19:33:54 by smclacke      #+#    #+#                  #
#    Updated: 2023/07/03 17:19:28 by dreijans      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


NAME			= minishell
DJOY			= djoyke
SAAR			= sarah

CFLAGS			= -Wall -Wextra
# -Werror
# LFLAGS			= -L$(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline
CC				= cc
INCLUDES		= -Iinclude -Iinclude/libft/include -lreadline
# IFLAGS			= -I$(HOME)/.brew/Cellar/readline/8.2.1/include

## MINISHELL ##

SRCS		=	main.c			\
				executor.c		\
				expander.c		\
				lexer.c			\
				parser.c

SRC_DIR			= src
SRC				= $(addprefix $(SRC_DIR)/, $(SRCS))

OBJ_DIR			= obj
OBJ				= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

## DJOYKE ##

SRCS_DJOY		=	main_djoy.c	\
					env_list.c \
					utils.c \
					ft_echo.c \
					ft_cd.c \
					ft_pwd.c \
					

DJOY_DIR		= src_djoy
SRC_DJOY		= $(addprefix $(DJOY_DIR)/, $(SRCS_DJOY))

OBJ_DJOY_DIR	= obj_djoy
OBJ_DJOY		= $(addprefix $(OBJ_DJOY_DIR)/, $(SRCS_DJOY:%.c=%.o))

## SARAH ##

SRCS_SAAR		= main_saar.c	\
					parser/parse.c	\
					parser/parser_utils.c	\
					lexer/lexer.c		\
					utils/error.c

SAAR_DIR		= src_saar
SRC_SAAR		= $(addprefix $(SAAR_DIR)/, $(SRCS_SAAR))

OBJ_SAAR_DIR	= obj_saar
OBJ_SAAR		= $(addprefix $(OBJ_SAAR_DIR)/, $(SRCS_SAAR:%.c=%.o))
OBJ_SAAR		= $(addprefix $(OBJ_SAAR_DIR)/, $(SRCS_SAAR:%.c=%.o))


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


all				: libft $(NAME)

djoy			: $(DJOY)

saar			: $(SAAR)

libft			:
	@ make -C include/libft


## EXECUTABLES

$(NAME)			:	$(OBJ)
	@ $(CC) $^ $(CFLAGS) $(LFLAGS) $(INCLUDES) include/libft/libft.a -o $(NAME)
	@ echo "${GREEN} ---> Minishell Made!${RESET}"

$(DJOY)			:	$(OBJ_DJOY)
	@ $(CC) $^ $(CFLAGS) $(LFLAGS) $(INCLUDES) include/libft/libft.a -o $(DJOY)
	@ echo "${PURPLE} ---> Djoyke Made!${RESET}"

$(SAAR)			:	$(OBJ_SAAR)
	@ $(CC) $^ $(CFLAGS) $(LFLAGS) $(INCLUDES) include/libft/libft.a -o $(SAAR)
	@ echo "${PURPLE} ---> Sarah Made!${RESET}"


## OBJECTS

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $(OBJ_DIR)
	@ $(CC) $(CFLAGS) $(IFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DJOY_DIR)/%.o: $(DJOY_DIR)/%.c
	@ mkdir -p $(OBJ_DJOY_DIR)
	@ $(CC) $(CFLAGS) $(IFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_SAAR_DIR)/%.o: $(SAAR_DIR)/%.c
	@ mkdir -p $(OBJ_SAAR_DIR)
	@ mkdir -p $(OBJ_SAAR_DIR)/parser
	@ mkdir -p $(OBJ_SAAR_DIR)/lexer
	@ mkdir -p $(OBJ_SAAR_DIR)/utils
	@ $(CC) $(CFLAGS) $(IFLAGS) $(INCLUDES) -c $< -o $@


clean		:
	@make -C include/libft clean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DJOY_DIR)
	@rm -rf $(OBJ_SAAR_DIR)

fclean		:
	@make -C include/libft fclean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DJOY_DIR)
	@rm -rf $(OBJ_SAAR_DIR)
	@rm -rf $(NAME)
	@rm -rf $(DJOY)
	@rm -rf $(SAAR)
	@echo "${YELLOW} // Minishell fCleaned!${RESET}"

re			: fclean all

.PHONY: all clean fclean re libft sarah djoyke
