/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execute.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 14:38:11 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/22 17:01:05 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

//forking based on input size lenght linked list passed
//pipes just need 2 and pass them on
//list input will look like:
//[cat(1 part in node)] -> [ls + la (2 parts in node)] -> outfile

void	ft_execute(t_command *command)
{
	int	fork_pid;

	while (command)
	{
		fork_pid = 0;
		if (fork_pid < 0)
			mini_error("fork", errno);
		if (fork_pid == 0)
		{
			printf("children made\n");
		}
		command = command->next;
	}
}

// void	child(argv, envp)
// {
// 	int	pipe_fd[2];
// 	int	fd_in;

// 	if (dup2(STDIN_FILENO, fd_in) == -1)
// 		mini_error("dup2", errno);
// 	while
// 	{
// 	}
// }
