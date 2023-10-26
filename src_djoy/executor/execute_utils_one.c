/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils_one.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 20:59:03 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/26 22:40:21 by dreijans      ########   odam.nl         */
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
			mini_error("dup2", errno);
	if (data->pipe_left[READ] != -1)
		if (dup2(data->pipe_left[READ], STDIN_FILENO) == -1)
			mini_error("dup2", errno);
	if (data->pipe_left[WRITE] != -1 && close(data->pipe_left[WRITE]) == -1)
		mini_error("dup2", errno);
	if (data->pipe_right[READ] != -1 && close(data->pipe_right[READ]) == -1)
		mini_error("dup2", errno);
}

/**
 * @param lst parser linked list
 * @param execute execute struct
 * @brief checks for redirects and enters redirect in or outfile function
 * @todo
 * does mini_error need to be syntax error or something elkse?
 * minishell 🍌cat < haha.txt < lol < Makefile > test2
[0]      cmd = cat      file = (null)   meta = (null)   str = (null)    n_cmd = 1
[1]      cmd = (null)   file = (null)   meta = <        str = (null)    n_cmd = 0
[2]      cmd = (null)   file = haha.txt meta = (null)   str = (null)    n_cmd = 0
[3]      cmd = (null)   file = (null)   meta = <        str = (null)    n_cmd = 0
[4]      cmd = (null)   file = lol      meta = (null)   str = (null)    n_cmd = 0
[5]      cmd = (null)   file = (null)   meta = <        str = (null)    n_cmd = 0
[6]      cmd = (null)   file = Makefile meta = (null)   str = (null)    n_cmd = 0
[7]      cmd = (null)   file = (null)   meta = >        str = (null)    n_cmd = 0
[8]      cmd = (null)   file = test2    meta = (null)   str = (null)    n_cmd = 0
count = [0]
minishell: lol: No such file or directory
minishell 🍌^C
➜  minishell git:(djoyke) ✗ bash    
dreijans@f0r3s15:~/Documents/rank3/minishell$ cat < haha.txt < lol < Makefile > test2
bash: lol: No such file or directory
maakt nog test 2 aan, bash doet dat niet
*/
void	redirect(t_parser *lst, t_execute *data)
{
	if (!lst->next)
		return ;
	lst = lst->next;
	while (lst && !lst->cmd)
	{
		if (check_redirect(lst) != 0)
		{
			redirect_infile(lst, data);
			redirect_heredoc(lst);
			redirect_outfile(lst, data);
		}
		lst = lst->next;
	}
}

/**
 * @param i int representing amount of times loop ran
 * @param count int representing amount of cmd's
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
 * @todo
 * check if we need to close data->hdoc_fd
*/
void	close_between(t_execute *data)
{
	if (data->pipe_left[READ] != -1 && close(data->pipe_left[READ]) == -1)
		mini_error("close", errno);
	if (data->pipe_left[WRITE] != -1 && close(data->pipe_left[WRITE]) == -1)
		mini_error("close", errno);
	if (data->pipe_right[WRITE] != -1 && close(data->pipe_right[WRITE]) == -1)
		mini_error("close", errno);
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
		mini_error("close", errno);
	if (data->pipe_left[WRITE] != -1 && close(data->pipe_left[WRITE]) == -1)
		mini_error("close", errno);
	if (data->pipe_right[WRITE] != -1 && close(data->pipe_right[WRITE]) == -1)
		mini_error("close", errno);
	if (data->pipe_right[READ] != -1 && close(data->pipe_right[READ]) == -1)
		mini_error("close", errno);
}
