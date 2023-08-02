/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:20:16 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/02 13:50:23 by smclacke      ########   odam.nl         */
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
# include <stdbool.h>

# define READ 0
# define WRITE 1

# define SUCCESS 0
# define ERROR -1

# define TRUE 1
# define FALSE 0

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
t_lexer			*micro_print_lexer(t_lexer *token);

//---- Parser ----//
typedef struct s_parser 
{
	void				*input;
	char				*str;
	char				*cmd;
	char				*sign;
	char				**path; // need to handle abso paths, doesnt do anything (:
	// char				*redirect; sign->redirect ? be specific or nah?
	char				*here_doc;
	struct s_lexer		*tokens;
	struct s_parser		*next;
	struct s_lexer		*par_tokens;
}	t_parser;

//---- parser.c ----//
t_parser		*micro_parser(t_lexer *tokens);

//---- parser_utils.c ----//
bool			micro_cmp_builtins(t_lexer *tokens);
bool			micro_cmp_signs(t_lexer *tokens);
bool			micro_first_token(t_lexer *tokens, t_parser *parser_struct);

//---- Expander ----//
typedef struct s_expand
{
	char				*sign;
	char				*str;
	char				*builtin;
	struct s_expand		*next;
	struct s_expand		*previous;
}						t_expand;

t_expand	*micro_expand(char **envp, t_parser *node);
bool		micro_check_for_meta(t_parser *node);
bool		shelly_check_for_builtin(t_parser *node);
t_expand	*shelly_expand_lstlast(t_expand *lst);
void		shelly_expand_lstadd_back(t_expand **lst, t_expand *new);

//---- Executor ----//
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*previous;
}							t_env;

/*environment*/
t_env		*micro_env_list(char **envp);
t_env		*micro_env_lstnew(void *key, void *value);
void		micro_get_key_value(char *str, char **key, char **value);
t_env		*micro_env_lstlast(t_env *lst);
void		micro_env_lstadd_back(t_env **lst, t_env *new);
void		micro_print_list(t_env *env);
void		micro_print_list_key(t_env *env);
void		micro_print_list_value(t_env *env);

//---- Built-in ----//
void		micro_cd(t_parser *node, t_env *env);
void		micro_echo(t_parser *node);
void		micro_env(t_env *env);
void		micro_pwd(char *path, t_env *env);
void		micro_export(t_parser *node, t_env *env);
void		micro_unset(t_parser *node, t_env *env);

/*execution*/
t_parser	*micro_build_process(t_parser *node, t_env *env);
t_parser	*micro_forks(t_parser *node, t_env *env, int fd_in, int *pipe_fd);
bool		micro_absolute_check(t_parser *node);
bool		micro_parse_path(t_env *env, t_parser *node);
char		*micro_find_path(t_env *env, t_parser *node);
void		micro_build(t_parser *node, t_env *env);

//----Utils----//
void		micro_error(char *string, int error);
int			micro_strcmp(char *s1, char *s2);
void		micro_check_for_builtin(t_parser *node, t_env *env);

//------------ Minishell -----------//

/**
 * everything that we share
 * add our structs that hold the info that we need to share/for minishell as a whole 
*/

typedef struct s_mini
{
	struct s_parser		tokens;
	struct s_env		environ;
}	t_mini;

#endif