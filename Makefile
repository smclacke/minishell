# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: smclacke <smclacke@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/24 19:33:54 by smclacke      #+#    #+#                  #
#    Updated: 2023/06/25 00:47:13 by smclacke      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
DJOY		= djoyke
SAAR		= sarah

CFLAGS		= -Wall -Wextra -Werror
CC			= cc
INCLUDES	= -Iinclude -Iinclude/libft/src

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

SRCS_DJOY		= main_djoy.c

DJOY_DIR		= src_djoy
SRC_DJOY		= $(addprefix $(DJOY_DIR)/, $(SRCS_DJOY))

OBJ_DJOY_DIR	= obj_djoy
OBJ_DJOY		= $(addprefix $(OBJ_DJOY_DIR)/, $(SRCS_DJOY:%.c=%.o))

## SARAH ##

SRCS_SAAR		= main_saar.c

SAAR_DIR		= src_saar
SRC_SAAR		= $(addprefix $(SAAR_DIR)/, $(SRCS_SAAR))

OBJ_SAAR_DIR	= obj_saar
OBJ_SAAR		= $(addprefix $(OBJ_SAAR_DIR)/, $(SRCS_SAAR:%.c=%.o))


## LIBFT ##

LIBFT_DIR		= include/libft

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

all			: libft $(NAME)

djoyke		: $(DJOY)

sarah		: $(SAAR)

libft	:
	@ make -C include/libft


$(NAME)	:	$(OBJ)
	@ echo "${WHITE} >>> Minishell compiling...${RESET}"
	@ $(CC) $^ $(CFLAGS) $(INCLUDES) include/libft/libft.a -o $(NAME)
	@ echo "${RED} ---> Minishell Made!${RESET}"

$(DJOY)	:	$(OBJ_DJOY)
	@ echo "${CYAN} >>> DJOYKE <3${RESET}"
	@ $(CC) $^ $(CFLAGS) $(INCLUDES) -o $(DJOY)
	@ echo "${RED} ---> Djoyke Made!${RESET}"

$(SAAR)	:	$(OBJ_SAAR)
	@ echo "${PURPLE} >>> SARAH  :D${RESET}"
	@ $(CC) $^ $(CFLAGS) $(INCLUDES) -o $(SAAR)
	@ echo "${RED} ---> Sarah Made!${RESET}"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $(OBJ_DIR)
	@ $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DJOY_DIR)/%.o: $(DJOY_DIR)/%.c
	@ mkdir -p $(OBJ_DJOY_DIR)
	@ $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_SAAR_DIR)/%.o: $(SAAR_DIR)/%.c
	@ mkdir -p $(OBJ_SAAR_DIR)
	@ $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
	@ echo "${BLUE} // Minishell fCleaned!${RESET}"

re			: fclean all

.PHONY: all clean fclean re libft sarah djoyke
