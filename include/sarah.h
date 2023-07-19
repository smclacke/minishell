/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sarah.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:10:39 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/19 16:26:19 by smclacke      ########   odam.nl         */
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

# define SUCCESS 0
# define ERROR -1

typedef enum	e_signs
{
	DQUOTE = 1,
	SQUOTE = 2,
	DOLLAR = 3,
	MORE = 4,
	MOREMORE = 5,
	LESS = 6,
	LESSLESS = 7,
	PIPE = 8
}		t_signs;


// LEXER
typedef	struct s_lexer
{
	void				*input;
	void				*token;
	t_signs				sign[8]; // do we need this and if so what do we do with it?
	struct s_lexer		*next;
}	t_lexer;

// --------- Lexer --------- //
t_lexer		*lexer(char *input);
char		**parse_input(char *input); // get rid of this when things sort of start to work

// --------- Split_input --------- //
char		**split_input(char *input);

// -------- Quotes --------//
int			closed_quotes(char *input);
char		*check_quotes(char *input);

// -------- Lexer Utils --------//
t_lexer		*list_last(t_lexer *list);
void		listadd_back(t_lexer **list, t_lexer *new);
t_lexer		*list_new(void *input);
void		parse_space(char *input);		// don't need this or at least not in lexer
t_lexer		*ft_print_tokens(t_lexer *token);



// PARSER 
typedef struct s_parser 
{
	struct t_lexer		*tokens;
}	t_parser;

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
