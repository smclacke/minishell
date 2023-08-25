/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   djoyke.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:04:53 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/25 15:58:35 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DJOYKE_H
# define DJOYKE_H

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

//---- Lexer ----//
typedef enum e_metas
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
	char				*squote;
	char				*dquote;
	char				*here_doc;
	struct s_parser		*next;
}	t_parser;

//----- lexer.c -----//
void		init_parser(t_parser *token);
t_parser	*lexer(char *input);

//----- lexer_utils.c -----//
t_parser	*lexer_listlast(t_parser *list);
void		lexer_listadd_back(t_parser **list, t_parser *new);
t_parser	*lexer_listnew(void *input);
t_parser	*shelly_print_list(t_parser *token);

// -------- Quotes --------//
char		*quote_tokens(char *input);
int			closed_quotes(char *input);
char		*check_quotes(char *input);

//---- parser.c ----//
t_parser	*parser(t_parser *tokens);

//---- parser_quotes.c ----//
bool		parser_check_quotes(char *tokens);
char		*remove_quotes(char *tokens);

//---- parser_utils.c ----//
bool		parser_cmp_squote(t_parser *param);
bool		parser_cmp_dquote(t_parser *param);
bool		parser_cmp_builtins(t_parser *param);
bool		parser_cmp_metas(t_parser *tokens);
bool		parser_cmp_abso(t_parser *tokens);

//---- Executor ----//
typedef struct s_env
{
	char				*key;
	char				*value;
	char				*full;
	struct s_env		*next;
	struct s_env		*previous;
}							t_env;

//---- Expander ----//
void		ft_expand(t_parser *lst, t_env **env);
bool		check_for_meta(t_parser *lst);
bool		check_for_builtin(t_parser *lst);

//----Environment----//
// t_env		*env_list(char **envp);
t_env		*env_list(char **envp, t_env *env);
t_env		*env_lstnew(void *key, void *value, char *full);
void		get_key_value(char *str, char **key, char **value);
t_env		*env_lstlast(t_env *lst);
void		env_lstadd_back(t_env **lst, t_env *new);
void		print_list(t_env *env);
void		print_list_key(t_env *env);
void		print_list_value(t_env *env);
char		**list_to_string(t_env *env);
void		print_env_list(t_env *lst);
void		print_list_full(t_env *env);

//---- Built-in ----//
void		free_all(t_env *env);
void		do_builtin(t_parser *node, t_env **env);
void		ft_cd(t_parser *lst, t_env **env);
void		access_and_change(t_env **env, t_parser *lst, char *o_d, char *c_d);
void		change_old_dir(t_env **env, char *str);
void		change_current_dir(t_env **env, char *str);
void		reassign_old_pwd(t_env **env, t_env *new, char *str, char *full);
void		ft_echo(t_parser *lst);
void		ft_env(t_env *env);
void		ft_pwd(void);
void		ft_export(t_parser *lst, t_env **env);
void		reassign_env(t_env **env, t_parser *node, char *n_k, char *n_v);
void		ft_unset(t_parser *lst, t_env **env);
void		mini_remove_env(char *str, t_env **env);

//----Execution----//
typedef struct s_execute
{
	int		fd_in;
	int		fork_pid;
	int		pipe_fd[2];
	char	**path;
	char	**env_array;
}				t_execute;

t_parser	*mini_forks(t_parser *lst, t_env *env, t_execute *data);
bool		absolute_check(t_parser *node);
bool		parse_path(t_env *env, t_execute *data);
char		*check_access(t_env *env, t_parser *node, t_execute *data);
void		ft_execute(t_env **env, t_parser *list);
void		build(t_parser *lst, t_env *env, t_execute *data);
void		init_execute_struct(t_execute *data, t_env *env);

//----Utils----//
void		mini_error(char *string, int error);
int			mini_strcmp(char *s1, char *s2);
int			mini_lstsize(t_env *lst);

//------------ Minishell -----------//
/**
 * everything that we share
 * add our structs that hold the info that we need to share/
 * for minishell as a whole 
*/

typedef struct s_mini
{
	struct s_parser		tokens;
	struct s_env		environ;
}	t_mini;

#endif