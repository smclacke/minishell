/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils_one.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 20:59:03 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/19 22:16:46 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param data execute struct
 * @brief dup2 pipes to STDIN_FILENO and STDOUT_FILENO
 * closes pipes that arent used in child process
*/
void	init_pipes_child(t_execute *data)
{
	if (data->pipe_right[WRITE] != -1)
		if (dup2(data->pipe_right[WRITE], STDOUT_FILENO) == -1)
			printf("dup child fail 1\n");
	if (data->pipe_left[READ] != -1)
		if (dup2(data->pipe_left[READ], STDIN_FILENO) == -1)
			printf("dup child fail 2\n");
	if (data->pipe_left[WRITE] != -1 && close(data->pipe_left[WRITE] == -1))
		printf("close child fail 1\n");
	if (data->pipe_right[READ] != -1)
		if (close(data->pipe_right[READ]) == -1)
			printf("close child fail 2\n");
}

/**
 * @param lst parser linked list
 * @param execute execute struct
 * @brief checks for redirects and enters redirect in or outfile function
*/
void	redirect(t_parser *lst, t_execute *data)
{
	lst = lst->next;
	while (lst && !lst->cmd)
	{
		if (check_redirect(lst) != 0)
		{
			redirect_infile(lst, data);
			redirect_outfile(lst, data);
		}
		lst = lst->next;
	}
}

/**
 * @param i int representing amount of times loop ran
 * @param count int representing amount of cmds in linked list
 * @brief initialises pipes and reassings pipes after each loop.
*/
void	init_pipe(int i, int count, t_execute *data)
{
	if (i == 0)
	{
		if (count == 1)
			return ;
		if (pipe(data->pipe_right) == -1)
			mini_error("pipe_right", errno);
		return ;
	}
	data->pipe_left[READ] = data->pipe_right[READ];
	data->pipe_left[WRITE] = data->pipe_right[WRITE];
	data->pipe_right[READ] = -1;
	data->pipe_right[WRITE] = -1;
	if (count > 1)
		if (pipe(data->pipe_right) == -1)
			mini_error("pipe_right", errno);
}

/**
 * @param data execute struct
 * @brief closes pipes when value is not -1. sets to -1 after closing
*/
void	close_between(t_execute *data)
{
	if (data->pipe_left[READ] != -1 && close(data->pipe_left[READ]) == -1)
		mini_error("close 1", errno);
	if (data->pipe_left[WRITE] != -1 && close(data->pipe_left[WRITE]) == -1)
		mini_error("close 2", errno);
	if (data->pipe_right[WRITE] != -1 && close(data->pipe_right[WRITE]) == -1)
		mini_error("close 5", errno);
	data->pipe_left[READ] = -1;
	data->pipe_left[WRITE] = -1;
	data->pipe_right[WRITE] = -1;
}

/**
 * @param data execute struct
 * @brief closes all the pipes when value is not -1. sets to -1 after closing
*/
void	close_all(t_execute *data)
{
	if (data->pipe_left[READ] != -1 && close(data->pipe_left[READ]) == -1)
		mini_error("close 3", errno);
	if (data->pipe_left[WRITE] != -1 && close(data->pipe_left[WRITE]) == -1)
		mini_error("close 4", errno);
	if (data->pipe_right[WRITE] != -1 && close(data->pipe_right[WRITE]) == -1)
		mini_error("close 5", errno);
	if (data->pipe_right[READ] != -1 && close(data->pipe_right[READ]) == -1)
		mini_error("close 6", errno);
}