/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 20:59:12 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/14 15:55:57 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param lst parser linked list
 * @param env  environment linked list
 * @param data execute struct
 * @brief checks for single builtin command and if there are redirects
 * executes the builtin and redirect function
 * @todo norm it
*/
bool	single_builtin_cmd(t_parser *lst, t_env **env, t_execute *data)
{
	int	count;
	int	cmd_type;

	count = lst->proc->proc_count;
	cmd_type = 0;
	if (count == 1)
	{
		cmd_type = check_for_builtin(lst);
		if (cmd_type != 0)
		{
			if (lst->proc->red_count != 0)
			{
				redirect(lst, data);
				// if (data->error == false)
				// 	return (true);
			}
			do_builtin(lst, env, cmd_type);
				return (true);
		}
		return (false);
	}
	return (false);
}

/**
 * @param lst parser linked list
 * @param env  environment linked list
 * @param data execute struct
 * @brief forks, checks if it didnt fail, enters child process
 * @todo exit code NORM
*/
void	init_fork(t_parser *lst, t_env **env, t_execute *data)
{
	data->fork_pid = fork();
	handle_signals(CHILD);
	if (data->fork_pid == -1)
		mini_error(E_GENERAL, lst);
	if (data->fork_pid == 0)
		mini_forks(lst, env, data);
}

/**
 * @param node node from parser linked list
 * @brief checks node->abso if it's an absolute path
 * @return true is absolute path
 * false if no absolute path
*/
bool	absolute_check(t_parser *node)
{
	if (!node->proc->cmd)
		return (false);
	if (!ft_strncmp(node->proc->cmd, "/", 1)
		&& access(node->proc->cmd, F_OK) == 0)
		return (true);
	if (!ft_strncmp(node->proc->cmd, "./", 2)
		&& access(node->proc->cmd, F_OK) == 0)
		return (true);
	if (!ft_strncmp(node->proc->cmd, "../", 3)
		&& access(node->proc->cmd, F_OK) == 0)
		return (true);
	return (false);
}

/**
 * @param lst parser linked list
 * @param env  environment linked list
 * @param data execute struct
 * @brief child execution process, calls init_pipes
 * init_forks and close_between in a while loop
 * @todo norm it
*/
void	pipeline(t_parser *lst, t_env **env, t_execute *data)
{
	int	count;
	int	i;

	count = lst->proc_count;
	i = 0;
	while (lst)
	{
		init_pipe(i, count, data, lst);
		init_fork(lst, env, data);
		close_between(data, lst);
		count--;
		i++;
		lst = lst->next;
	}
}

/**
 * @param lst parser linked list
 * @param execute execute struct
 * @brief checks for redirects and enters redirect in or outfile function
 * @todo remove printf statement
 * @note keeping hd_count check since func used much, i.e. mini_forks
 * 		- when used with multi procs, check hd stuff...
*/
void	redirect(t_parser *lst, t_execute *data)
{
	if (lst->proc->red_count == 0)
		return ;
	if (!redirect_infile(lst->proc, data))//why again?
	{
		data->error = false;
		return ;
	}
	redirect_heredoc(lst);
	redirect_outfile(lst->proc, data);
	redirect_append(lst->proc, data);
}
