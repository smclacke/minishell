/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   djoyke.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:04:53 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/10 19:29:28 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DJOYKE_H
# define DJOYKE_H

# include "libft/include/libft.h"
# include "prompt.h"
# include "colour.h"
// # include "sarah.h"
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
# include <sys/wait.h>

# define READ 0
# define WRITE 1

# define SUCCESS 0
# define ERROR -1

# define TRUE 1
# define FALSE 0

/**
 * @brief	specifies the different variable types of tokens from the
 * 			lexer that are parsed and then given to the executor
 * @param	cmd: first string in each process without redirect char
 * @param	meta: pipe, more, less, moremore, lessless. 
 * 			**dollar is excluded and handled as a string
 * @param	file: in and out files; after more, less and moremore chars
 * @param	str:  limiter for here_doc (string after <<) and all other input
*/
typedef struct s_parser
{
	void				*input;
	char				*cmd;
	char				*meta;
	char				*file;
	char				*str;
	struct s_parser		*next;
}				t_parser;

// utils
void			free_tokens(t_parser *tokens);

// lexer
//---------- lexer ----------//
t_parser		*lexer(char *input);

//-------- lexer_utils --------//
t_parser		*lexer_listlast(t_parser *list);
void			lexer_listadd_back(t_parser **list, t_parser *new);
t_parser		*lexer_listnew(void *input);
t_parser		*shelly_print_list(t_parser *token);

//---------- token ----------//
char			**parse_input(char *input);

//-------- token_size --------//
int				start_token(char *input, int old_start);
int				len_token(char *input, int len);

//-------- token_utils --------//
int				is_meta(char *input);
int				space_or_meta(int c);
char			*which_quote(char *input);
int				next_quote(char *input, char c);

// parser
//-------- parser --------//
t_parser		*parser(t_parser *tokens);

//-------- parser_utils --------//
t_parser		*handle_pipe(t_parser *data, int *flag);
int				is_pipe(void *input);
char			*is_redirect(void *input);
t_parser		*shelly_parser_print(t_parser *tokens);


//---- Executor ----//
typedef struct s_env
{
	char				*key;
	char				*value;
	char				*full;
	struct s_env		*next;
	struct s_env		*previous;
	int					has_value;
}							t_env;

//---- Expander ----//
typedef struct s_expand
{
	char				*before_dollar;
	char				*env_value;
	char				*comp_str;
	int					i;
	int					j;
}							t_expand;

void			free_remain_struct(t_expand *data);
// void			get_compare_str(t_parser *node, t_expand *exp, int i, int j);
void			get_compare_str(char *str, t_expand *exp, int i, int j);
void			reassing_before_dollar(t_expand *exp);
// void			dollar(t_parser *node, t_env **env, t_expand *exp, int len);
char			*dollar(char *str, t_env **env, t_expand *exp, int len);
// void			return_exp(t_parser *node, t_expand *exp);
char			*return_exp(char *str, t_expand *exp);
// void			get_before_dollar(t_parser *node, t_expand *exp, int i);
void			get_before_dollar(char *str, t_expand *exp, int i);
int				get_check_value(t_expand *exp, t_env **env);
// int				get_check_value(char *str, t_env **env);
bool			check_for_meta(t_parser *lst);
void			ft_expand(t_parser *lst, t_env **env);
bool			check_for_builtin(t_parser *lst);
void			save_expanded(t_expand *exp);
// void			exp_dollar(t_parser *node, t_env **env, t_expand *exp, int len);
char			*exp_dollar(char *str, t_env **env, t_expand *exp, int len);

//----Environment----//
t_env			*env_list(char **envp, t_env *env);
t_env			*env_lstnew(void *key, void *value, char *full, int h_v);
int				get_key_value(char *str, char **key, char **value);
t_env			*env_lstlast(t_env *lst);
void			env_lstadd_back(t_env **lst, t_env *new);
void			print_list(t_env *env);
void			print_list_key(t_env *env);
void			print_list_value(t_env *env);
char			**list_to_string(t_env *env);
void			print_env_list(t_env *lst);
void			print_list_full(t_env *env);

//---- Built-in ----//
void			free_all(t_env *env);
void			do_builtin(t_parser *node, t_env **env);
bool			word_check(t_parser *lst);
void			ft_cd(t_parser *lst, t_env **env);
void			put_custom_error(t_parser *node, char *cmd);
void			ft_echo(t_parser *lst);
void			ft_env(t_env *env);
void			ft_exit(t_parser *lst);
void			ft_pwd(void);
void			ft_export(t_parser *lst, t_env **env);
bool			reassign_env(t_env **env, t_parser *node, char *n_k, char *n_v);
void			ft_unset(t_parser *lst, t_env **env);
void			mini_remove_env(char *str, t_env **env);
void			reasing_value(char *temp, char *str, t_env *head);

//----Execution----//
typedef struct s_execute
{
	int		fd_in;
	int		fork_pid;
	int		pipe_fd[2];
	char	**path;
	char	**env_array;
}				t_execute;

t_parser		*mini_forks(t_parser *lst, t_env *env, t_execute *data);
bool			absolute_check(t_parser *node);
bool			parse_path(t_env *env, t_execute *data);
char			*check_access(t_env *env, t_parser *node, t_execute *data);
void			ft_execute(t_env **env, t_parser *list);
void			build(t_parser *lst, t_env *env, t_execute *data);
void			init_execute_struct(t_execute *data, t_env *env);

//----Utils----//
void			mini_error(char *string, int error);
int				mini_strcmp(char *s1, char *s2);
int				mini_lstsize(t_env *lst);
void			print_parser_list(t_parser *lst);
void			free_strs(char *str, char *str2);

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
