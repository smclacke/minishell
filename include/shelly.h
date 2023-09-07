/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shelly.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 14:31:31 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/07 15:08:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELLY_H
# define SHELLY_H

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
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>

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
	void				*input;
	char				*meta;
	// char				*file;
	// enum e_files		*file_type[4]; // do i want this?
	// enum e_metas		*meta_type[5];
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_command
{
	void				*input;
	char				*cmd; // first arg if not a redirect and whatever comes after a pipe
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

//---- meta_split.c ----//
int					ms_word_count(t_parser *tokens);
int					ms_word_len(t_parser *tokens);
t_parser			*ms_make_words(t_parser *tokens);
t_parser			**meta_split(t_parser *tokens);

//---- parser_utils.c ----//
void				init_cmd_struct(t_command *cmds);
void				init_red_struct(t_redirect *reds);
bool				is_pipe(t_parser *tokens);
bool				is_redirect(t_parser *tokens);
bool				file_attached(t_parser *tokens);
t_parser			*shelly_parser_print(t_parser *tokens);



//---------------DJOYKE-----------//

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
bool		word_check(t_parser *node);
void		ft_cd(t_parser *lst, t_env **env);
void		put_custom_error(t_parser *node, char *cmd);
void		access_and_change(t_env **env, t_parser *lst, char *o_d, char *c_d);
void		change_old_dir(t_env **env, char *str);
void		change_current_dir(t_env **env, char *str);
void		reassign_old_pwd(t_env **env, t_env *new, char *str, char *full);
void		ft_echo(t_parser *lst);
void		ft_env(t_env *env);
void		ft_exit(t_parser *node);
void		ft_pwd(void);
void		ft_export(t_parser *lst, t_env **env);
bool		reassign_env(t_env **env, t_parser *node, char *n_k, char *n_v);
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
void		print_parser_list(t_parser *lst);

#endif
