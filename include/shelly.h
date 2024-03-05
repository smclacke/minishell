/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shelly.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 14:31:31 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/05 13:41:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELLY_H
# define SHELLY_H

# include "libft/include/libft.h"
# include "structs.h"
# include "prompt.h"
# include "colour.h"
# include <unistd.h>
# include <string.h>
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
//---------- more_space ----------//
int				input_redir(char *input);
int				set_flag(t_procs *proc, int i);
int				count_str_util(t_procs *proc, char **process, int i);
int				get_strs_util(t_procs *proc, char **process, int i);
int				copy_strs(t_procs *proc, char *process);

//---------- parser_erros ----------//
int				syntax_error(char *str);
void			general_error(char *str);
void			malloc_error(t_parser *par, t_procs *proc,
					char **str, int exit_code);

//---------- free_procs ----------//
void			free_procs(t_procs *proc);
void			free_proc_arrs(t_parser *proc);
void			free_util(t_parser *list, char ***arrs, char **arr, char *str);

//---------- utils ----------//
int				ft_abs(int i);
void			free_lots_stuff(t_parser *proc);
void			ft_free_process(t_parser *proc);
void			free_parser(t_parser *procs);

				// lexer
//---------- lexer ----------//
char			**lexer(char *input);

//-------- lexer_utils --------//
int				is_meta(char *input);
int				space_or_meta(int c);
int				is_same_quote(int c, char *quote_type);
char			*which_quote(char *input);
int				next_quote(char *input, char c);

//-------- tokens --------//
bool			is_space(char *input);
int				shelly_strcmp(char *s1, char *s2);
int				start_token(char *input, int old_start);
int				len_token(char *input, int len);

//-------- meta_check --------//
int				meta_check(char *input, char *q, int i, int ret);

				// parser
//-------- parser --------//
t_parser		*parse_input(t_parser *procs, char *input);

//-------- parser utils --------//
int				is_pipe(void *input);
int				count_procs(char **tokens);
t_parser		*parser_listlast(t_parser *list);
void			parser_listadd_back(t_parser **list, t_parser *new);
t_parser		*parser_listnew(t_procs *proc);

//-------- sort_procs --------//
int				sort_each_proc(t_procs *proc, char **proc_arr);
int				get_procs(t_parser *proc);

//-------- get_procs --------//
int				get_reds(t_procs *proc, char **process);
int				get_hds(t_procs *proc, char **process);
int				get_strs(t_procs *proc, char **process);

//-------- proc_utils --------//
int				count_reds(char **process);
int				count_strs(t_procs *proc, char **process);
int				count_hds(char **process);
int				proc_redir(char *input);
int				make_proc_arr(t_parser *proc, int proc_i, int proc_size);

				// expander
//------------------ expand -------------------//
void			ft_expand(t_parser *lst, t_env **env);

//------------------- expand_dollar --------------------//
int				save_extra_string(t_expand *str, char *input, int i);
int				first_bit(t_expand *str, char *input);
int				handle_dollars(t_parser *par, t_expand *str,
					t_env **env, int i);
void			dollar(t_parser *par, t_expand *str, t_env **env);
void			expand_dollar(t_parser *lst, t_env **env);

//-------------------- expand_quotes -------------------//
void			expand_quotes(t_parser *tokens);

//-------------------- remove_quotes -------------------//
void			remove_quotes(char *str);

//----------------- expand_quote_utils ------------------//
int				check_qs(char *str);
int				check_space(char *str);
int				quote_type(int str);

//------------------ expand_utils ------------------//
int				add_to_expand(t_expand *str, char *copy_str);
void			do_reds(t_parser *tmp, t_expand *str, t_env **env);
void			do_hds(t_parser *tmp, t_expand *str, t_env **env);
void			do_strs(t_parser *tmp, t_expand *str, t_env **env);
void			do_cmd(t_parser *tmp, t_expand *str, t_env **env);

//------------------ expand_utils_2 ------------------//
int				get_check_value(t_expand *str, t_env **env);
void			exit_exp(t_parser *par, t_expand *str);
int				ex_str(int c);
int				is_dollar_or_quote(int c);

//------------------- hd_expand --------------------//
char			*hd_expand(t_env **env, char *read_line);

//------------------- s_quotes --------------------//
int				squote_bit(t_expand *str, char *input, int i);

//------------------- d_quotes --------------------//
int				dquote_bit(t_parser *par, t_expand *str, t_env **env, int i);

//----------------- dollars ------------------//
int				dollar_expand(t_expand *str, t_env **env);
int				dollar_bit(t_expand *str, char *input, t_env **env, int i);

//------------------ signals ------------------//
void			handle_signals(int proc);

				// ALL DJOYKE PROTOS //
int				check_for_builtin(t_parser *node);
bool			redirect_outfile(char *str, t_execute *data, t_parser *lst);
bool			redirect_infile(char *str, t_execute *data, t_parser *lst);
bool			redirect_append(char *str, t_execute *data, t_parser *lst);
void			init_heredoc(t_parser *lst, t_env **env);
bool			redirect(t_parser *lst, t_execute *data);
void			redirect_heredoc(t_parser *lst);

//----Environment----//
t_env			*env_list(char **envp, t_env *env);
t_env			*env_lstnew(void *key, void *value, char *full, int h_v);
int				get_key_value(char *str, char **key, char **value);
void			env_lstadd_back(t_env **lst, t_env *new);
char			**list_to_string(t_env *env);
void			free_env(t_env **lst);

//---- Built-in ----//
void			do_builtin(t_parser *node, t_env **env, int cmd_type);
bool			word_check(t_parser *lst, char *key);
void			ft_cd(t_parser *lst, t_env **env);
bool			too_many_args(t_parser *lst);
void			no_such_file(char *str, t_parser *lst);
void			put_custom_error(t_parser *node, char *str, char *cmd);
void			ft_echo(t_parser *lst, t_env **env);
void			ft_env(t_env *env, t_parser *lst);
void			ft_exit(t_parser *lst);
void			ft_pwd(t_parser *head);
void			ft_export(t_parser *lst, t_env **env);
void			make_node(t_env **env, t_export var);
void			replace_node(t_env *lst, t_export var);
void			ft_unset(t_parser *lst, t_env **env);
void			reassign_values(char *cwd, t_env *node, t_parser *head);
void			free_all(t_env *env);

//----Executor----//
void			mini_forks(t_parser *lst, t_env **env, t_execute *data);
bool			absolute_check(t_parser *node);
void			execute(t_env **env, t_parser *list);
void			init_execute_struct(t_execute *data);
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
void			free_strs(char *str1, char *str2);
void			mini_error(int exit_enum, t_parser *lst);
int				mini_strcmp(char *s1, char *s2);
int				mini_lstsize(t_env *lst);
char			*ft_getenv(t_env *env, char *str);
void			*mini_malloc(int size);
char			*mini_strjoin(char const *s1, char const *s2);
char			*mini_strdup(const char *s1);
char			*mini_substr(char const *s, unsigned int start, size_t len);
void			exit_status(int status, t_parser *lst);
void			redir_file_error(char *str, t_parser *lst);
void			write_permission_error(char *str, t_parser *lst);
bool			dir_error(char *str, t_parser *lst);
void			write_to_file(t_parser *lst, char *rl, t_env **env, int file);
void			executable_check(t_parser *lst, t_execute *data, char *exec);
void			put_exit_error(t_parser *node);
void			infile_permission_error(t_parser *node, char *str);
void			no_valid_command(t_parser *node, char *str);
bool			redir_error(t_parser *lst, char *str);
void			close_hd_fd(t_parser *lst);
void			unlink_heredoc(t_parser *lst);

#endif
