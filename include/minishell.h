/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:20:16 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/26 16:44:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/include/libft.h"
# include "prompt.h"
# include "colour.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <errno.h>

# define READ 0
# define WRITE 1
# define SUCCESS 0
# define ERROR -1

//------------ MICRO_SHELL ----------//

//---- Lexer ----//
typedef enum e_signs
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

// t_signs				sign[8]; // do we need this and if so what do we do with it?
typedef	struct s_lexer
{
	void				*input;
	void				*token;
	struct s_lexer		*next;
}	t_lexer;

//----- lexer.c -----//
t_lexer			*micro_lexer(char *input);

//----- lexer_utils.c -----//
t_lexer			*micro_lexer_listlast(t_lexer *list);
void			micro_lexer_listadd_back(t_lexer **list, t_lexer *new);
t_lexer			*micro_lexer_listnew(void *input);
t_lexer			*micro_ft_print_tokens(t_lexer *token);


//---- Parser ----//
typedef struct s_parser 
{
	char				*str;
	char				*cmd;
	char				*redirect;
	char				*here_doc;
	struct s_lexer		*tokens;
	struct s_parser		*par_tokens;
}	t_parser;

//---- parser.c ----//
// bool			micro_check_valid(t_lexer *tokens);
// t_parser		*micro_define_tokens(t_lexer *tokens);
t_parser		*micro_parser(t_lexer *tokens);

//---- parser_utils.c ----//
bool			micro_cmp_builtins(t_lexer *tokens);
bool			micro_cmp_signs(t_lexer *tokens);
bool			micro_first_token(t_lexer *tokens);


//---- Expander ----//

//---- Executor ----//
typedef struct s_env
{
	char				*key;
	char				*value;
	// char				full;
	struct s_env		*next;
	struct s_env		*previous;
}							t_env;

void	micro_set_pipes(s_parser *node, t_env *env)

//---- Utils ----//
void		micro_mini_error(char *string, int error);

//------------ Minishell -----------//

/**
 * everything that we share
 * add our structs that hold the info that we need to share/for minishell as a whole 
*/
typedef	struct s_mini
{
	struct	s_parser	tokens;
	struct	s_env		environ;
}	t_mini;

#endif