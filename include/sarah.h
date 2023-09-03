/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sarah.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:10:39 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/03 18:01:39 by smclacke      ########   odam.nl         */
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

typedef enum	e_files
{
	S_INFILE, // standard infile
	S_OUTFILE, // standard outfile
	D_INFILE, // this is heredoc (<<infile)
	D_OUTFILE // this is append mode to outfile
}		t_files;

typedef enum	e_metas
{
	E_MORE,
	E_MOREMORE,
	E_LESS,
	E_LESSLESS,
	E_PIPE
}		t_metas;

typedef struct	s_redirect
{
	char				*file;
	enum e_files		*file_type[4]; // do i want this?
	enum e_metas		*meta_type[5];
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_command
{
	void				*info;
	char				*cmd;
	char				*strs; // all shit after cmd up to any redirect (could be another cmd but in this case its str, or flag but just called str)
	struct s_command	*next;
}			t_command;

typedef struct s_parser
{
	void				*input;
	struct s_command	*cmd_list;
	struct s_redirect	*redirect_list;
	struct s_parser		*next;
}	t_parser;


//----- lexer.c -----//
t_parser			*lexer(char *input);

// -------- Quotes --------//
bool				closed_quotes(char *input);
bool				shelly_check_quotes(char *tokens);
char				**ft_split_shelly(char *input);

// --------Quote utils ------//
int					lq_isquote(char c);
int					lq_what_to_split(char c);
int					which_quote(char c);
int					lq_count_words(char *input);
int					lq_word_length(char *input);
int					quote_len(char *input);

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
void				init_cmd_struct(t_command *cmds);
bool				is_pipe(t_parser *tokens);
bool				is_redirect(t_parser *tokens);
bool				file_attached(t_parser *tokens);
t_parser			*shelly_parser_print(t_parser *tokens);

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
