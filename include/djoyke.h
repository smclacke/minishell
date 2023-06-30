/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   djoyke.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:04:53 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/30 12:59:30 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DJOYKE_H
# define DJOYKE_H

# include "../include/libft/src/libft.h"
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
	char				*content;//envp content
	struct s_env		*next;
	struct s_env		*previous;
}							t_env;

/* list making functions*/
void	mini_lstadd_back(t_env **lst, t_env *new);
t_env	*mini_lstlast(t_env *lst);
t_env	*mini_lstnew(void *content);
void	list_env(char **envp, t_env **env);
void	print_list(t_env *env);
void	error(char *string, int error);

#endif