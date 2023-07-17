/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execute.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 14:38:11 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/17 16:27:21 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

//forking based on input size lenght linked list passed
//pipes just need 2 and pass them on
//list input will look like:
//[cat(1 part in node)] -> [ls + la (2 parts in node)] -> outfile

void	ft_execute(int argc, char **argv)
{
	int	count;
	// int	pipe_fd[2];
	int	fork_pid;
	int	i;

	count = argc -1;
	i = 0;
	(void) argv;
	while (count != 0)
	{
		fork_pid = 0;
		if (fork_pid < 0)
			mini_error("fork", errno);
		if (fork_pid == 0)
			printf("children made\n");
		count --;
		i++;
	}
}

// void	ft_execute(int argc, char **argv)
// {
// 	int	count;
// 	int	pipe_fd[2];

// 	count = argc - 1;
// 	(void) argv;
// 	while (count != 0)
// 	{
// 		if (pipe(pipe_fd) == -1)
// 			mini_error("pipe", errno);
// 		printf("pipe created\n");
// 		count --;
// 	}
// }
