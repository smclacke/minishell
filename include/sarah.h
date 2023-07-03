/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sarah.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:10:39 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/03 15:42:09 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT BI_YELLOW".~❃~."BI_PURPLE".~⚘~."BI_CYAN".~✿~."RESET

#include "libft/include/libft.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdbool.h>

# define OPEN_QUOTE = 1
# define CLOSED_QUOTE = 0

# define SUCCESS 0
# define ERROR -1

// EXITCODES
typedef enum e_exitcode
{
	E_USAGE = 0,
	E_GENERAL = 1,
	E_BUILTIN = 2,
	E_EXEC = 126,
	E_COMMAND_NOT_FOUND = 127,
	E_EXIT_INVALID_ARG = 128,
	E_FATAL_SIGNAL = 128,
	E_CTRL_C = 130,
	E_UNKNOWN = 225
}					t_exitcode;

// LEXER STRUCT
typedef	struct s_lexer
{
	char				*input;
	struct s_lexer		*next;
}	t_lexer;


// PARSER STRUCT
typedef struct s_parser 
{
	char	*input_pars;
	char	**cmd;
}	t_parser;


// PROTOTYPES
// --------- Lexer --------- //
t_lexer		*ft_print_tokens(t_lexer *token);
void		parse_space(char **input);
int			is_token(char *str);
int			token_len(char *input);
char		*make_token(char *input);
t_lexer		*lexer(char *input);

// -------- Lexer Utils --------//
int			second_quote(char *input, char c);

// --------- Parser --------- //

// ------- Parser Utils ------- //
char		*check_empty(char *cmd);


// --------- UTILS -------- //
// --------- Errors -------- //
void		error_no_cmd(void);
void		error_space(char *cmd);


// COLOURS
# define RESET "\033[0m"
# define RED "\033[1;91m"
# define GREEN "\033[1;92m"
# define YELLOW "\033[1;93m"
# define BLUE "\033[1;94m"
# define PURPLE "\033[1;95m"
# define CYAN "\033[1;96m"
# define WHITE "\033[1;97m"
# define BLACK "\033[1;90m"
// COLOURS BOLD
# define B_BLACK "\e[1;30m"
# define B_RED "\e[1;31m"
# define B_GREEN "\e[1;32m"
# define B_YELLOW "\e[1;33m"
# define B_BLUE "\e[1;34m"
# define B_PURPLE "\e[1;35m"
# define B_CYAN "\e[1;36m"
# define B_WHITE "\e[1;37m"
// COLOURS BOLD HIGH INTENSITY
# define BI_BLACK "\e[1;90m"
# define BI_RED "\e[1;91m"
# define BI_GREEN "\e[1;92m"
# define BI_YELLOW "\e[1;93m"
# define BI_BLUE "\e[1;94m"
# define BI_PURPLE "\e[1;95m"
# define BI_CYAN "\e[1;96m"
# define BI_WHITE "\e[1;97m"

#endif
