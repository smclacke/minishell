/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_forks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/22 18:25:02 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/22 18:32:08 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

//[cat(1 part in node)] -> [ls + la (2 parts in node)] -> outfile

/**
 * @param command linked list containing commands and atributes
 * @param env linked list containing environment
 * @brief sets pipe to be reused in every child process
*/
void	set_pipes(t_command *command, t_env *env)
{
	int	pipe_fd[2];
	int	fd_in;

	if (dup2(STDIN_FILENO, fd_in) == -1)
		mini_error("dup2", errno);
	while (command)
	{
		if (pipe(pipe_fd) == -1)
			mini_error("pipe", errno);
		playground(command, env);
		if (dup2(pipe_fd[READ], fd_in) == -1)
			mini_error("dup2", errno);
		close(pipe_fd[READ]);
		command = command->next;
	}
}
/**
 * @param command linked list containing commands and atributes
 * @param env linked list containing environment
 * @brief makes child process and executes in it
*/
void	set_forks(t_command *command, t_env *env)
{
	int	fork_pid;

	fork_pid = fork();
	if (fork_pid == -1)
		mini_error("fork", errno);
	if (fork_pid == 0)
	{
		printf("children made\n");
	}
	command = command->next;
}
