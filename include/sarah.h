/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sarah.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:10:39 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/20 16:34:41 by smclacke      ########   odam.nl         */
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

typedef struct s_parser 
{
	void				*input;
	void				*tokens;
	char				*str;
	char				*cmd;
	char				*meta;
	char				*abso;
	char				*flag;
	char				*squote;
	char				*dquote;
	char				*here_doc;
	struct s_parser		*previous;
	struct s_parser		*next;
}	t_parser;

//----- lexer.c -----//
bool				closed_quotes(char *input);
bool				shelly_check_quotes(char *tokens);
t_parser			*lexer(char *input);

// -------- Quotes --------//
char				**ft_split_shelly(char *input);

// --------Quote utils ------//
int					lq_isquote(char c);
int					lq_what_to_split(char c);
int					which_quote(char c);
int					lq_count_words(char *input);
int					lq_word_length(char *input);
int					quote_len(char *input);
int					quote_length(char *input);

//----- lexer_utils.c -----//
void				init_parser(t_parser *token);
t_parser			*lexer_listlast(t_parser *list);
void				lexer_listadd_back(t_parser **list, t_parser *new);
t_parser			*lexer_listnew(void *input);
t_parser			*shelly_print_list(t_parser *token);


// PARSER

//---- parser.c ----//
t_parser			*parser(t_parser *tokens);

//---- parser_quotes.c ----//
// bool				parser_check_quotes(char *tokens);
// char				*remove_quotes(char *tokens);

//---- parser_utils.c ----//
bool				parser_cmp_squote(t_parser *param);
bool				parser_cmp_dquote(t_parser *param);
bool				parser_cmp_builtins(t_parser *param);
bool				parser_cmp_metas(t_parser *tokens);
bool				parser_cmp_abso(t_parser *tokens);


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
