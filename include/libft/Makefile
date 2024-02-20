# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: smclacke <smclacke@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/12 14:53:21 by smclacke      #+#    #+#                  #
#    Updated: 2024/02/20 15:04:08 by smclacke      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
ARCHIVE		= ar rcs
RM			= rm -f

SRCS		=	is_func/ft_ispipe.c				\
				is_func/ft_ishex.c				\
				is_func/ft_isalpha.c			\
    			is_func/ft_isalnum.c			\
    			is_func/ft_isascii.c			\
    			is_func/ft_isdigit.c			\
    			is_func/ft_isprint.c			\
				is_func/ft_isquote.c			\
				is_func/ft_isdquote.c			\
				is_func/ft_issquote.c			\
				is_func/ft_isspace.c			\
				is_func/ft_ismeta.c				\
				is_func/ft_isdollar.c			\
				is_func/ft_dollar.c				\
				is_func/ft_spaced.c				\
				is_func/ft_isquest.c			\
    			strs/ft_strchr.c				\
    			strs/ft_strrchr.c				\
    			strs/ft_strlen.c				\
    			strs/ft_strnstr.c				\
    			strs/ft_strncmp.c				\
				strs/ft_strcpy.c				\
    			strs/ft_strlcat.c				\
    			strs/ft_strlcpy.c				\
				strs/ft_strcmp.c				\
    			strs/ft_split.c					\
    			strs/ft_strjoin.c				\
    			strs/ft_substr.c				\
    			strs/ft_striteri.c				\
    			strs/ft_strtrim.c				\
    			strs/ft_strmapi.c				\
    			strs/ft_strdup.c				\
    			mem/ft_bzero.c					\
    			mem/ft_memset.c					\
    			mem/ft_memcpy.c					\
    			mem/ft_memcmp.c					\
    			mem/ft_memmove.c				\
    			mem/ft_memchr.c					\
    			mem/ft_calloc.c					\
    			convert/ft_atoi.c				\
				convert/ft_atof.c				\
    			convert/ft_itoa.c				\
    			convert/ft_tolower.c			\
    			convert/ft_toupper.c			\
				convert/ft_lower_str.c			\
				convert/ft_upper_str.c			\
				convert/ft_atoi_base.c			\
    			puts/ft_putchar_fd.c			\
    			puts/ft_putendl_fd.c			\
    			puts/ft_putnbr_fd.c				\
    			puts/ft_putstr_fd.c				\
				puts/ft_putchar.c				\
				puts/ft_putendl.c				\
				puts/ft_putstr.c				\
    			list/ft_lstadd_back.c			\
    			list/ft_lstadd_front.c			\
    			list/ft_lstclear.c				\
    			list/ft_lstdelone.c				\
    			list/ft_lstiter.c				\
    			list/ft_lstlast.c				\
    			list/ft_lstmap.c				\
    			list/ft_lstnew.c				\
    			list/ft_lstsize.c				\
				arr/ft_arrlen.c					\
				arr/ft_free_arr.c				\
				error/ft_error.c				\
				gnl/get_next_line.c				\
				gnl/get_next_line_utils.c		\
				printf/ft_printf_utils.c		\
				printf/ft_printf.c

SRC_DIR		= src
SRC			= $(addprefix $(SRC_DIR)/, $(SRCS))

OBJ_DIR		= obj
OBJS		= $(SRCS:%.c=%.o)
OBJ			= $(addprefix $(OBJ_DIR)/, $(OBJS))

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

all: $(NAME)

$(NAME): $(OBJ)
	@ echo "${YELLOW} >>> libft compiling...${RESET}"
	@ $(ARCHIVE) $(NAME) $(OBJ)
	@ echo "${GREEN} ---> libft Made!${RESET}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)/arr
	@ mkdir -p $(OBJ_DIR)/convert
	@ mkdir -p $(OBJ_DIR)/error
	@ mkdir -p $(OBJ_DIR)/gnl
	@ mkdir -p $(OBJ_DIR)/is_func
	@ mkdir -p $(OBJ_DIR)/list
	@ mkdir -p $(OBJ_DIR)/mem
	@ mkdir -p $(OBJ_DIR)/printf
	@ mkdir -p $(OBJ_DIR)/puts
	@ mkdir -p $(OBJ_DIR)/strs
	@ $(CC) $(CFLAGS) -c -o $@ $<

clean:
	@ $(RM) -rf $(OBJ_DIR)

fclean: clean
	@ $(RM) $(NAME)
	@ echo "${YELLOW} /// libft fCleaned!${RESET}"

re: fclean all

.PHONY: all clean fclean re
