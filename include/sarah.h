/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sarah.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:10:39 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/03 14:35:47 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SARAH_H
# define SARAH_H

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

# define READ 0
# define WRITE 1

# define SUCCESS 0
# define ERROR -1

# define TRUE 1
# define FALSE 0

typedef enum	e_metas
{
	DQUOTE = 1,
	SQUOTE = 2,
	DOLLAR = 3,
	MORE = 4,
	MOREMORE = 5,
	LESS = 6,
	LESSLESS = 7,
	PIPE = 8
}		t_metas;

// LEXER
typedef	struct s_lexer
{
	void				*input;
	void				*token;
	struct s_lexer		*next;
}	t_lexer;

//----- lexer.c -----//
void			init_lexer(t_lexer *token_list);
t_lexer			*lexer(char *input);

//----- lexer_utils.c -----//
t_lexer			*lexer_listlast(t_lexer *list);
void			lexer_listadd_back(t_lexer **list, t_lexer *new);
t_lexer			*lexer_listnew(void *input);
t_lexer			*print_lexer(t_lexer *token);

// -------- Quotes --------//
// int				sign_tokens(char *input);
char			*quote_tokens(char *input);
int				closed_quotes(char *input);
char			*check_quotes(char *input);

// PARSER
typedef struct s_parser 
{
	char				*str;
	char				*cmd;
	char				*meta; // probs won't use
	char				*abso;
	char				*here_doc;
	struct s_lexer		*tokens;
	struct s_parser		*next;
}	t_parser;

//---- parser.c ----//
void			init_parser(t_parser *parser_struct);
t_parser		*parser(t_lexer *tokens);

//---- parser_quotes.c ----//
bool			parser_check_quotes(char *tokens);
char			*remove_quotes(char *tokens);

//---- parser_utils.c ----//
bool			parser_cmp_builtins(t_lexer *param);
bool			parser_cmp_metas(t_lexer *tokens);
bool			parser_cmp_abso(t_lexer *tokens);


// UTILS
// --------- Error -------- //

// OTHER FUNCTIONS
// ------------ Other ---------// // not sure if necessary, just keeping for now
void		parse_space(char *input);
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
