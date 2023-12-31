/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shelly.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 14:31:31 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/10 20:26:34 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef SHELLY_H
# define SHELLY_H

# include "libft/include/libft.h"
# include "structs.h"
# include "prompt.h"
# include "colour.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>

				// utils
bool			is_space(char *input);
int				shelly_strcmp(char *s1, char *s2);
void			free_only_tokens(t_parser *tokens);
void			free_tokens(t_parser *tokens);
int				get_n_cmds(t_parser *tokens);

				// print
void			print_expand_vals(t_expand *str);
void			shelly_print_list(t_parser *token);
t_parser		*shelly_parser_print(t_parser *tokens);
t_parser		*print_the_full_thing(t_parser *tokens);

				// lexer
//---------- lexer ----------//
t_parser		*lexer(char *input);

//-------- lexer_utils --------//
t_parser		*lexer_listlast(t_parser *list);
void			lexer_listadd_back(t_parser **list, t_parser *new);
t_parser		*lexer_listnew(char *input);

//---------- token ----------//
char			**parse_input(char *input);

//-------- token_size --------//
int				start_token(char *input, int old_start);
int				len_token(char *input, int len);

//-------- token_utils --------//
int				is_meta(char *input);
int				space_or_meta(int c);
int				is_same_quote(int c, char *quote_type);
char			*which_quote(char *input);
int				next_quote(char *input, char c);

				// parser
//-------- parser --------//
t_parser		*parser(t_parser *tokens);

//-------- parser_utils --------//
int				is_meta_no_pipe(char *input);
t_parser		*handle_pipe(t_parser *data, int *flag);
int				is_pipe(void *input);
char			*is_redirect(void *input);

//---------- sort ----------//
t_parser		*sort_list(t_parser *tokens);

//---------- sort_utils ----------//
t_parser		*add_new_limit(t_parser *tmp, t_parser *new_list, char *str);
t_parser		*add_new_str(t_parser *tmp, t_parser *new_list, char *str);
t_parser		*add_new_file(t_parser *tmp, t_parser *new_list, char *file);
t_parser		*add_new_meta(t_parser *tmp, t_parser *new_list, char *meta);
t_parser		*add_new_cmd(t_parser *tmp, t_parser *new_list, char *cmd);

				// expander
//------------------- hd_expand --------------------//
char			*hd_expand(t_env **env, char *read_line);

//------------------- s_quotes --------------------//
int				squote_bit(t_expand *str, char *input, int i);

//------------------- d_quotes --------------------//
int				dquote_bit(t_expand *str, char *input, t_env **env, int i);

//----------------- dollars ------------------//
int				dollar_expand(t_expand *str, t_env **env);
int				dollar_bit(t_expand *str, char *input, t_env **env, int i);

//------------------- expand_dollar --------------------//
int				save_extra_string(t_expand *str, char *input, int i);
int				first_bit(t_expand *str, char *input);
void			expand_dollar(t_parser *lst, t_expand *str, t_env **env);

//----------------- expand_quote_utils ------------------//
int				check_quotes(char *str);
void			copy_and_increment(char *new_str, char *str, int *i, int *j);
int				check_space(char *str);
int				quote_type(int str);

//-------------------- expand_quotes -------------------//
void			expand_quotes(t_parser *tokens);

//------------------ expand_is_utils ------------------//
int				expandable_str(int c);
int				is_dollar_or_quote(int c);

//------------------ expand_utils ------------------//
int				add_to_expand(t_expand *str, char *copy_str);
int				get_check_value(t_expand *str, t_env **env);
int				set_expand_string(t_parser *tmp, t_expand *str);

//------------------ expand -------------------//
void			ft_expand(t_parser *lst, t_env **env);

//------------------ signals ------------------//
void			handle_signals(int proc);

				// ALL DJOYKE PROTOS //
bool			check_for_builtin(t_parser *node);
void			redirect_outfile(t_parser *head, t_execute *data);
bool			redirect_infile(t_parser *head, t_execute *data);
void			redirect_append(t_parser *head, t_execute *data);
void			init_heredoc(t_parser *lst, t_env **env);
void			redirect(t_parser *lst, t_execute *data);
void			redirect_heredoc(t_parser *lst);

//----Environment----//
t_env			*env_list(char **envp, t_env *env);
t_env			*env_lstnew(void *key, void *value, char *full, int h_v);
int				get_key_value(char *str, char **key, char **value);
t_env			*env_lstlast(t_env *lst);
void			env_lstadd_back(t_env **lst, t_env *new);
void			print_list(t_env *env);
void			print_list_key(t_env *env);
void			print_list_value(t_env *env);
char			**list_to_string(t_env *env, t_parser *lst);
void			free_env(t_env **lst);
char			*get_full(char *str);

//---- Built-in ----//
void			free_all(t_env *env);
void			do_builtin(t_parser *node, t_env **env);
bool			word_check(t_parser *lst);
void			ft_cd(t_parser *lst, t_env **env);
bool			too_many_args(t_parser *lst);
void			no_such_file(t_parser *lst);
void			put_custom_error(t_parser *node, char *cmd);
void			ft_echo(t_parser *lst, t_env **env);
void			ft_env(t_env *env, t_parser *lst);
void			ft_exit(t_parser *lst);
void			ft_pwd(t_parser *head);
void			ft_export(t_parser *lst, t_env **env);
char			**null_check(t_parser *temp);
void			make_node(t_parser *node, t_env **env, char *n_k, char *n_v);
void			replace_str(t_env *head, t_parser *node, char *n_k, char *n_v);
void			ft_unset(t_parser *lst, t_env **env);
void			reassign_values(char *cwd, t_env *node, t_parser *head);

//----Executor----//
void			mini_forks(t_parser *lst, t_env **env, t_execute *data);
bool			absolute_check(t_parser *node);
void			execute(t_env **env, t_parser *list);
void			init_execute_struct(t_execute *data);
bool			check_redirect(t_parser *node);
void			free_data(t_execute *data);
void			close_all(t_execute *data, t_parser *lst);
void			close_between(t_execute *data, t_parser *lst);
void			init_pipe(int i, int count, t_execute *data, t_parser *lst);
void			init_pipes_child(t_execute *data, t_parser *lst);
void			init_fork(t_parser *lst, t_env **env, t_execute *data);
bool			single_builtin_cmd(t_parser *lst, t_env **env, t_execute *data);
void			pipeline(t_parser *lst, t_env **env, t_execute *data);
char			**get_argv(t_parser *lst);
void			put_execute_error(t_parser *node);
void			put_permission_error(t_parser *node);

//----Utils----//
void			mini_error(int exit_enum, t_parser *lst);
int				mini_strcmp(char *s1, char *s2);
int				mini_lstsize(t_env *lst);
void			free_strs(char *str, char *str2);
char			*ft_getenv(t_env *env, char *str);
int				list_iter(t_parser *lst);


void			print_array(char **arr);

#endif
