/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils_one.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 20:59:03 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/08 21:12:45 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param data execute struct
 * @brief dup2 pipes to STDIN_FILENO and STDOUT_FILENO
 * closes pipes that arent used in child process
 * @todo exit codes, < file goes wrong in line 24 why??? god knows, yeah no
*/
void	init_pipes_child(t_execute *data, t_parser *lst)
{
	if (data->pipe_right[WRITE] != -1)
		if (dup2(data->pipe_right[WRITE], STDOUT_FILENO) == -1)
			mini_error(E_GENERAL, lst);
	if (data->pipe_left[READ] != -1)
		if (dup2(data->pipe_left[READ], STDIN_FILENO) == -1)
			mini_error(E_GENERAL, lst);
	if (data->pipe_left[WRITE] != -1 && close(data->pipe_left[WRITE]) == -1)
		mini_error(E_GENERAL, lst);
	if (data->pipe_right[READ] != -1 && close(data->pipe_right[READ]) == -1)
		mini_error(E_GENERAL, lst);
}

/**
 * @param i int representing amount of times loop ran
 * @param count int representing amount of cmd's
 * @brief initialises pipes and reassings pipes after each loop.
 * @todo error codes
*/
void	init_pipe(int i, int count, t_execute *data, t_parser *lst)
{
	if (i == 0)
	{
		if (count == 1)
			return ;
		if (pipe(data->pipe_right) == -1)
			mini_error(E_GENERAL, lst);
		return ;
	}
	data->pipe_left[READ] = data->pipe_right[READ];
	data->pipe_left[WRITE] = data->pipe_right[WRITE];
	data->pipe_right[READ] = -1;
	data->pipe_right[WRITE] = -1;
	if (count > 1)
		if (pipe(data->pipe_right) == -1)
			mini_error(E_GENERAL, lst);
}

/**
 * @param data execute struct
 * @brief closes pipes when value is not -1. sets to -1 after closing
 * @todo error codes
*/
void	close_between(t_execute *data, t_parser *lst)
{
	if (data->pipe_left[READ] != -1 && close(data->pipe_left[READ]) == -1)
		mini_error(E_GENERAL, lst);
	if (data->pipe_left[WRITE] != -1 && close(data->pipe_left[WRITE]) == -1)
		mini_error(E_GENERAL, lst);
	if (data->pipe_right[WRITE] != -1 && close(data->pipe_right[WRITE]) == -1)
		mini_error(E_GENERAL, lst);
	data->pipe_left[READ] = -1;
	data->pipe_left[WRITE] = -1;
	data->pipe_right[WRITE] = -1;
}

/**
 * @param data execute struct
 * @brief closes all the pipes when value is not -1. sets to -1 after closing
 * @todo error codes
*/
void	close_all(t_execute *data, t_parser *lst)
{
	if (data->pipe_left[READ] != -1 && close(data->pipe_left[READ]) == -1)
		mini_error (E_GENERAL, lst);
	if (data->pipe_left[WRITE] != -1 && close(data->pipe_left[WRITE]) == -1)
		mini_error (E_GENERAL, lst);
	if (data->pipe_right[WRITE] != -1 && close(data->pipe_right[WRITE]) == -1)
		mini_error (E_GENERAL, lst);
	if (data->pipe_right[READ] != -1 && close(data->pipe_right[READ]) == -1)
		mini_error (E_GENERAL, lst);
}
