/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   djoyke.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:04:53 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/31 14:50:37 by dreijans      ########   odam.nl         */
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
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>

# define READ 0
# define WRITE 1

# define SUCCESS 0
# define ERROR -1

# define TRUE 1
# define FALSE 0

// EXITCODES
typedef enum e_exit
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
}					t_exit;

/**
 * @brief	specifies the different variable types of tokens from the
 * 			lexer that are parsed and then given to the executor
 * @param	cmd: first string in each process without redirect char
 * @param	meta: pipe, more, less, moremore, lessless. 
 * 			**dollar is excluded and handled as a string
 * @param	file: in and out files; after more, less and moremore chars
 * @param	str:  limiter for here_doc (string after <<) and all other input
 * @param	flag: useful util var
 * @param	n_cmd: total amount of commands is stored in first node
 * @param	exit_code: enums to set exitcode at different
 * 			stages of process, saved to pass through the program
*/
typedef struct s_parser
{
	void				*input;
	char				*cmd;
	char				*meta;
	char				*file;
	char				*str;
	int					flag;
	int					n_cmd;
	int					hd_fd;
	enum e_exit			exit_code;
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

/**
 * @brief	linked list containing the environment
 * @param	key: string containing the key part of the environment
 * @param	value: string containing the value part of the environment
 * @param	full: string containing full line of the environment
 * 			including semicolon.
 * @param	next: env struct pointing to the next node in the linked list
 * 			if no next then it points to NULL.
 * @param	has_value: int used as checkpoint if the key has a value
*/
typedef struct s_env
{
	char				*key;
	char				*value;
	char				*full;
	struct s_env		*next;
	int					has_value;
}							t_env;

//---- Expander ----//
typedef struct s_expand
{
	char				*before_dollar;
	char				*env_value;
	char				*comp_str;
}							t_expand;

/**
 * @brief	struct containing variables needed for execution process
 * @param	fork_pid: int to store fork_pid in
 * @param	pipe_left: pipe used to read and write to in process
 * @param	pipe_right: pipe used to read and write to in process
 * @param	path: 2d array storing the path to a command.
 * @param	env_array: 2d array storing environment from environment linked list
 * @param	in: int storing fd for infile
 * @param	out: int storing fd for outfile
 * @param	count: int storing amount of commands in parser linked list
 * @param	fd: int storing a fd
 * @todo	do I need fd?
*/
typedef struct s_execute
{
	pid_t			fork_pid;
	int				pipe_left[2];
	int				pipe_right[2];
	char			**path;
	char			**env_array;
	int				in;
	int				out;
	int				count;
	int				fd;
}						t_execute;

void			free_remain_struct(t_expand *data);
int				get_check_value(t_expand *exp, t_env **env);
bool			check_for_meta(t_parser *lst);
bool			check_for_builtin(t_parser *node);
void			save_expanded(t_expand *exp);
void			redirect_outfile(t_parser *head, t_execute *data);
void			redirect_infile(t_parser *head, t_execute *data);
void			redirect_append(t_parser *head, t_execute *data);
void			init_heredoc(t_parser *lst);
void			redirect(t_parser *lst, t_execute *data);
void			redirect_heredoc(t_parser *lst);
char			*set_heredoc_name(int i);
void			setup_heredoc(t_parser *lst, char *str, int i);
void			write_to_heredoc(t_parser *lst, char *file_name);
void			write_to_file(char *read_line, int file);
void			infile_error(t_parser *head);

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
void			free_env(t_env **lst);

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
void			ft_unset(t_parser *lst, t_env **env);
void			reasing_value(char *temp, char *str, t_env *head);

//----Executor----//
void			mini_forks(t_parser *lst, t_env **env, t_execute *data);
bool			absolute_check(t_parser *node);
void			execute(t_env **env, t_parser *list);
void			init_execute_struct(t_execute *data);
bool			check_redirect(t_parser *node);
void			free_data(t_execute *data);
void			close_all(t_execute *data);
void			close_between(t_execute *data);
void			init_pipe(int i, int count, t_execute *data);
void			init_pipes_child(t_execute *data);
void			init_fork(t_parser *lst, t_env **env, t_execute *data);
bool			single_builtin_cmd(t_parser *lst, t_env **env, t_execute *data);
void			child_builtin_cmd(t_parser *lst, t_env **env, t_execute *data);
char			**get_argv(t_parser *lst);

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
