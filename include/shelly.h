/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shelly.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 14:31:31 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/01 19:22:57 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELLY_H
# define SHELLY_H

#include "libft/include/libft.h"
#include "structs.h"
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


				// utils
int					shelly_strcmp(char *s1, char *s2);
void				free_tokens(t_parser *tokens);
int					get_n_cmds(t_parser *tokens);
void				print_expand_vals(t_expand *str);
t_parser			*print_the_full_thing(t_parser *tokens);



				// lexer
//---------- lexer ----------//
t_parser			*lexer(char *input);

//-------- lexer_utils --------//
t_parser			*lexer_listlast(t_parser *list);
void				lexer_listadd_back(t_parser **list, t_parser *new);
t_parser			*lexer_listnew(char *input);
t_parser			*shelly_print_list(t_parser *token);

//---------- token ----------//
char				**parse_input(char *input);

//-------- token_size --------//
int					start_token(char *input, int old_start);
int					len_token(char *input, int len);

//-------- token_utils --------//
int					is_meta(char *input);
int					is_meta_no_pipe(char *input);
int					space_or_meta(int c);
int					is_same_quote(int c, char *quote_type);
char				*which_quote(char *input);
int					next_quote(char *input, char c);



				// parser
//-------- parser --------//
t_parser			*parser(t_parser *tokens);

//-------- parser_utils --------//
t_parser			*handle_pipe(t_parser *data, int *flag);
int					is_pipe(void *input);
char				*is_redirect(void *input);
t_parser			*shelly_parser_print(t_parser *tokens);

//---------- sort ----------//
t_parser			*sort_list(t_parser *tokens);

//---------- sort_utils ----------//
t_parser			*add_new_str(t_parser *tmp, t_parser *new_list, char *str);
t_parser			*add_new_file(t_parser *tmp, t_parser *new_list, char *file);
t_parser			*add_new_meta(t_parser *tmp, t_parser *new_list, char *meta);
t_parser			*add_new_cmd(t_parser *tmp, t_parser *new_list, char *cmd);



				// expander
//-------------------- quotes -------------------//
char				*remove_quotes(char *str);
void				expand_quotes(t_parser *tokens);

//----------------- quote_utils ------------------//
void				increment(int *len, int *i);
int					check_quotes(char *str);
int					check_space(char *str);
int					quote_type(int str);
int					len_quotes(char *str);

//------------------- dollar --------------------//
void				expand_dollar(t_parser *lst, t_env **env, t_expand *str);

//----------------- dollar_expand ------------------//
char				*check_rest(t_expand *str, t_env **env, int i);
char				*check_first(t_expand *str);

//------------------ dollar_utils ------------------//
char				*check_if_expand(char *str);

//------------------ expand -------------------//
void				ft_expand(t_parser *lst, t_env **env);

//------------------ expand_utils ------------------//
int					get_check_value(t_expand *str, t_env **env);



				// ALL DJOYKE PROTOS //
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

#endif
