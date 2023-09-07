/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:20:16 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 15:29:42 by smclacke      ########   odam.nl         */
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

// LEXER
typedef struct s_parser 
{
	void				*input;
	void				*tokens;
	char				*str;
	char				*cmd;
	char				*meta;
	char				*abso;
	char				*squote;
	char				*dquote;
	char				*here_doc;
	struct s_parser		*next;
}	t_parser;

//----- lexer.c -----//
void				init_parser(t_parser *token);
t_parser			*lexer(char *input);

//----- lexer_utils.c -----//
t_parser			*lexer_listlast(t_parser *list);
void				lexer_listadd_back(t_parser **list, t_parser *new);
t_parser			*lexer_listnew(void *input);
t_parser			*shelly_print_list(t_parser *token);

// -------- Quotes --------//
char				*quote_tokens(char *input);
int					closed_quotes(char *input);
char				*check_quotes(char *input);

// PARSER

//---- parser.c ----//
t_parser			*parser(t_parser *tokens);

//---- parser_quotes.c ----//
bool				parser_check_quotes(char *tokens);
char				*remove_quotes(char *tokens);

//---- parser_utils.c ----//
bool				parser_cmp_squote(t_parser *param);
bool				parser_cmp_dquote(t_parser *param);
bool				parser_cmp_builtins(t_parser *param);
bool				parser_cmp_metas(t_parser *tokens);
bool				parser_cmp_abso(t_parser *tokens);


//---- Expander ----//
// typedef struct s_expand
// {
// 	char				*sign;
// 	char				*str;
// 	char				*builtin;
// 	char				*cmd;
// 	struct s_expand		*next;
// 	struct s_expand		*previous;
// }						t_expand;

// void		*micro_expand(t_parser *node);
// bool		micro_check_for_meta(t_parser *node);
bool		shelly_check_for_builtin(t_parser *node);
// t_expand	*shelly_expand_lstlast(t_expand *lst);
// void		shelly_expand_lstadd_back(t_expand **lst, t_expand *new);

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
void		micro_cd(t_parser *lst, t_env *env);
void		micro_echo(t_parser *lst);
void		micro_env(t_env *env);
void		micro_pwd(void);
void		micro_export(t_parser *lst, t_env *env);
void		micro_unset(t_parser *lst, t_env *env);

/*execution*/
// t_parser	*micro_build_process(t_parser *node, t_env *env);
// t_parser	*micro_forks(t_parser *node, t_env *env, int fd_in, int *pipe_fd);
// bool		micro_absolute_check(t_parser *node);
// bool		micro_parse_path(t_env *env, t_parser *node);
// char		*micro_find_path(t_env *env, t_parser *node);
// void		micro_build(t_parser *node, t_env *env);
void		micro_execute(char **envp, t_parser *list);
void		micro_build(t_parser *lst, t_env *env);
void		micro_check_for_meta(t_parser *lst);

//----Utils----//
void		micro_error(char *string, int error);
int			micro_strcmp(char *s1, char *s2);
void		micro_check_for_builtin(t_parser *lst, t_env *env);

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