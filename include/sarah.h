/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sarah.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:10:39 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/18 15:24:17 by smclacke      ########   odam.nl         */
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

# define OPEN_QUOTE = 0
# define CLOSED_QUOTE = 1

# define SUCCESS 0
# define ERROR -1

# define FOUND 1
# define NOPE 0

// enum e_parser
// {
// 	PIPE = 0
	
// }

// LEXER STRUCT
typedef	struct s_lexer
{
	void				*input;
	struct s_lexer		*token;
	struct s_lexer		*next;
}	t_lexer;

// PARSER STRUCT
typedef struct s_parser 
{
	struct t_lexer		*tokens;
}	t_parser;


// PROTOTYPES

// LEXER
// --------- Lexer --------- //
char		*make_token(char *parsed_token);
t_lexer 	*lexer(char *input);
char		**parse_input(char *input);

// -------- Quotes --------//
int			closed_quotes(char *input);
char		*check_quotes(char *input);

// -------- Lexer Utils --------//
t_lexer		*list_last(t_lexer *list);
void		listadd_back(t_lexer **list, t_lexer *new);
t_lexer		*list_new(void *input);
void		parse_space(char *input);
t_lexer		*ft_print_tokens(t_lexer *token);


// PARSER
// --------- Parser --------- //
// ------- Parser Utils ------- //
// char		*check_empty(char *cmd);

// UTILS
// --------- Error -------- //
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
