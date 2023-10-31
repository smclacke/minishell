

$(OBJ_MICRO_DIR)/%.o: $(MICRO_DIR)/%.c
	@ mkdir -p $(OBJ_MICRO_DIR)
	@ mkdir -p $(OBJ_MICRO_DIR)/parser
	@ mkdir -p $(OBJ_MICRO_DIR)/lexer
	@ mkdir -p $(OBJ_MICRO_DIR)/expand
	@ mkdir -p $(OBJ_MICRO_DIR)/executor
	@ mkdir -p $(OBJ_MICRO_DIR)/builtin
	@ $(CC) $(CFLAGS) $(IFLAGS) $(INCLUDES) -c $< -o $@


$(MICRO_SHELL)	:	$(OBJ_MICRO)
	@ $(CC) $^ $(CFLAGS) $(LFLAGS) $(IFLAGS) $(INCLUDES) include/libft/libft.a -o $(MICRO_SHELL)
	@ echo "${WHITE}our micro mini shell${RESET}"
	# @ ./micro



## MICRO_SHELL ##

SRCS_MICRO		= main.c						\
					lexer/lexer.c				\
					lexer/lexer_utils.c			\
					parser/parser.c				\
					lexer/parser_utils.c		\
					parser/parser_quotes.c		\
					builtin/micro_cd.c			\
					builtin/micro_echo.c		\
					builtin/micro_env.c			\
					builtin/micro_export.c		\
					builtin/micro_pwd.c			\
					builtin/micro_unset.c		\
					executor/micro_env.c 		\
					executor/micro_execute.c	\
					executor/micro_utils.c		\
					expander/micro_expand.c 
					

MICRO_DIR		= micro_shell
SRC_MICRO		= $(addprefix $(MICRO_DIR)/, $(SRCS_MICRO))


OBJ_MICRO_DIR	= obj_micro
OBJ_MICRO		= $(addprefix $(OBJ_MICRO_DIR)/, $(SRCS_MICRO:%.c=%.o))


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
