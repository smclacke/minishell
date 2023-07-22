/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_forks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/22 18:25:02 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/22 18:41:28 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/**
 * @param input linked list containing commands and atributes
 * @param env linked list containing environment
 * @brief sets pipe to be reused in every child process
*/
void	set_pipes(t_command *input, t_env *env)
{
	int	pipe_fd[2];
	int	fd_in;

	if (dup2(STDIN_FILENO, fd_in) == -1)//dupes standard input to fd_in
		mini_error("dup2", errno);
	if (pipe(pipe_fd) == -1)
		mini_error("pipe", errno);
	while (input->command)
	{
		set_forks(input, env);
		input->command = input->command->next;
	}
	if (dup2(pipe_fd[READ], fd_in) == -1)
		mini_error("dup2", errno);
	close(pipe_fd[READ]);
}

/**
 * @param input linked list containing commands and atributes
 * @param env linked list containing environment
 * @brief makes child process and executes in it
*/
void	set_forks(t_command *input, t_env *env)
{
	int	fork_pid;

	fork_pid = fork();
	if (fork_pid == -1)
		mini_error("fork", errno);
	if (fork_pid == 0)
	{
		printf("children made\n");
		while (input->arg)
		{
			//needed?
		}
	}
}
//[cat(1 part in node)] -> [ls + la (2 parts in node)] -> outfile
