/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   djoyke.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:04:53 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/21 17:34:48 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DJOYKE_H
# define DJOYKE_H

# include "libft/include/libft.h"
// # include "../include/minishell.h"
# include "colour.h"
# include "prompt.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include <errno.h>
# include <stddef.h>

# define __null 0

# define READ 0
# define WRITE 1

/* struct for the env, prepped to be doubly, for now singularly linked */
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*previous;
}							t_env;

/* struct for the commands, prepped to be doubly, for now singularly linked */
typedef struct s_command
{
	char					**arg;
	struct s_command		*next;
	struct s_command		*previous;
}							t_command;

/* list making functions */
void	mini_lstadd_back(t_env **lst, t_env *new);
t_env	*mini_lstlast(t_env *lst);
t_env	*mini_lstnew(void *key, void *value);
t_env	*env_list(char **envp);
void	get_key_value(char *str, char **key, char **value);

/* built-in utils and functions */
void	*ft_echo(char **argv);
void	ft_cd(char *argv);
void	ft_pwd(char *path);
void	ft_export(char **argv, t_env *env);
void	ft_unset(char *argv, t_env *env);
void	ft_env(t_env *env);

/* utils */
void	print_list(t_env *env);
void	print_list_key(t_env *env);
void	print_list_value(t_env *env);
int		ft_strcmp(const char *s1, const char *s2);
void	mini_error(char *string, int error);
void	check_for_builtin(char **argv, t_env *env);//for now index 1

/* fake input */
t_command	*command_lstnew(char **command);
t_command	*command_lstlast(t_command *lst);
void		command_lstadd_back(t_command **lst, t_command *new);
t_command	*init_command(void);
void		print_list_command(t_command *list);

/* execute */
// void	ft_execute(int argc, char **argv, char **envp);

#endif