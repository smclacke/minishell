/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_forks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/22 18:25:02 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/22 18:25:05 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

//forking based on input size lenght linked list passed
//pipes just need 1 and pass them on
//list input will look like:
//[cat(1 part in node)] -> [ls + la (2 parts in node)] -> outfile
/**
 * @param s1 string to compare
 * @param s1 string or char to compare with
 * @brief compares 2 strings replace by the libft version without -n
 * @return difference if different or 0
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
 * @param s1 string to compare
 * @param s1 string or char to compare with
 * @brief compares 2 strings replace by the libft version without -n
 * @return difference if different or 0
*/
void	set_forks(command, env)
{
	int	fork_pid;

	fork_pid = fork();
	if (fork_pid == -1)
		mini_error("fork", errno);
	else if (fork_pid == 0)
	while (command)
	{
		if (fork_pid < 0)
			mini_error("fork", errno);
		if (fork_pid == 0)
		{
			printf("children made\n");
			day_care(command, env);
		}
		command = command->next;
	}
}
