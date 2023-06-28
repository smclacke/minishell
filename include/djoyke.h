/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   djoyke.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:04:53 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/28 14:17:45 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/src/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stdbool.h>

# define PROMPT "hey Djoyke $"
# define READ 0
# define WRITE 1

typedef struct s_env
{
	char		*env_node;
	s_env		*next;
}							t_env;

#endif