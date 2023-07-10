/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   djoyke.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:04:53 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/10 20:27:31 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DJOYKE_H
# define DJOYKE_H

# include "libft/include/libft.h"
// # include "../include/minishell.h"
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

# define PROMPT "hey Djoyke $"
# define READ 0
# define WRITE 1

/* struct for the env, prepped to be doubly, for now singularly linked*/
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*previous;
}							t_env;

/* list making functions*/
void	mini_lstadd_back(t_env **lst, t_env *new);
t_env	*mini_lstlast(t_env *lst);
t_env	*env_list(char **envp);

/* built-in utils and fucntions */
void	*ft_echo(char **argv);
void	ft_cd(char *argv);
void	ft_pwd(char *path);
void	ft_export(char **argv, t_env env);

/* utils */
void	print_list(t_env *env);
int		ft_strcmp(const char *s1, const char *s2);
void	mini_error(char *string, int error);
void	check_for_builtin(char **argv, t_env *env);//for now index 1

#endif