/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:13:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/26 15:38:57 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	micro_execute(char **envp)
{
	env = micro_env_list(char **envp);
	micro_set_pipes(node, env);
}


/**
 * @param node linked list containing commands and atributes
 * @param env linked list containing environment
 * @brief sets pipe to be reused in every child process
 * @todo change name into something else its not just setting pipes
*/
void	micro_set_pipes(t_parser *node, t_env *env)
{
	int	pipe_fd[2];
	int	fd_in;

	fd_in = 0;
	if (dup2(STDIN_FILENO, fd_in) == -1)
		micro_error("dup2", errno);
	while (node->cmd)
	{
		if (pipe(pipe_fd) == -1)
			micro_error("pipe", errno);
		set_forks(node, env, fd_in, pipe_fd);
		if (dup2(pipe_fd[READ], fd_in) == -1)
			micro_error("dup2", errno);
		close(pipe_fd[READ]);
		node = node->next;
	}
}
