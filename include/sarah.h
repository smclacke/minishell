/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sarah.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:10:39 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/12 17:24:22 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/include/libft.h"
#include "prompt.h"
#include "colour.h"
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

# define FOUND 1
# define NOPE 0


// LEXER STRUCT
// for tokens (i hope) it is ok to just have a t_list
// for parser, need a beefier struct :):)
typedef	struct s_lexer
{
	char				*input;
	t_list				*token;
}	t_lexer;

// PARSER STRUCT
typedef struct s_parser 
{
	char	*input_pars;
	char	**cmd;
}	t_parser;


// PROTOTYPES

// LEXER
// --------- Lexer --------- //
char 		*find_tokens(char *input);
char		*parse_token(char *input);
char		*make_token(char *parsed_token);
t_list 		*lexer(char *input);

// --------- Tokens --------- //
char		*find_dollar(char *input);
char 		*find_redirect(char *input);
char		*find_delimiter(char *input);
char		*find_built_ins(char *input);

// -------- Quotes --------//
int			closed_quotes(char *input);
char		*find_quote(char *input);


// -------- Lexer Utils --------//
int			second_quote(char *input, char c);
void		parse_space(char *input);
t_list		*ft_print_tokens(t_list *token);


// PARSER
// --------- Parser --------- //

// ------- Parser Utils ------- //
char		*check_empty(char *cmd);

// UTILS
// --------- UTILS -------- //
// --------- Errors -------- //
void		error_no_cmd(void);
void		error_space(char *cmd);

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

#endif
