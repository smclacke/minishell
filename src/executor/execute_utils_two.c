/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 20:59:12 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/10 18:05:59 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param lst parser linked list
 * @param env  environment linked list
 * @param data execute struct
 * @brief checks for single builtin command and if there are redirects
 * executes the builtin and redirect function
*/
bool	single_builtin_cmd(t_parser *lst, t_env **env, t_execute *data)
{
	int	count;

	count = lst->n_cmd;
	if (count <= 1)
	{
		if (check_for_builtin(lst) || lst->meta)
		{
			redirect(lst, data);
			if (data->error == false)
				return (true);
			do_builtin(lst, env);
			return (true);
		}
	}
	return (false);
}

/**
 * @param lst parser linked list
 * @param env  environment linked list
 * @param data execute struct
 * @brief forks, checks if it didnt fail, enters child process
 * @todo exit code NORM do I need to WAIT here
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
	if (!node->cmd)
		return (false);
	if (!ft_strncmp(node->cmd, "/", 1)
		&& access(node->cmd, F_OK) == 0)
		return (true);
	if (!ft_strncmp(node->cmd, "./", 2)
		&& access(node->cmd, F_OK) == 0)
		return (true);
	if (!ft_strncmp(node->cmd, "../", 3)
		&& access(node->cmd, F_OK) == 0)
		return (true);
	return (false);
}

/**
 * @param lst parser linked list
 * @param env  environment linked list
 * @param data execute struct
 * @brief child execution process, calls init_pipes
 * init_forks and close_between in a while loop
 * @todo which version if statement? remove printf statement
*/
void	pipeline(t_parser *lst, t_env **env, t_execute *data)
{
	int	count;
	int	i;

	count = lst->n_cmd;
	i = 0;
	while (lst)
	{
		// if (count >= 0)
		// if (count >= 1 && lst->cmd)
		if ((count >= 1 && lst->cmd) || (count == 0 && lst->meta))
		{
			init_pipe(i, count, data, lst);
			init_fork(lst, env, data);
			close_between(data, lst);
			count--;
			i++;
		}
		lst = lst->next;
	}
}

/**
 * @param lst parser linked list
 * @param execute execute struct
 * @brief checks for redirects and enters redirect in or outfile function
 * @todo remove printf statement
*/
void	redirect(t_parser *lst, t_execute *data)
{
	if (!lst->next)
		return ;
	if (!lst->meta)
		lst = lst->next;
	while (lst && !lst->cmd)
	{
		if (check_redirect(lst) != 0)
		{
			if (!redirect_infile(lst, data))
			{
				data->error = false;
				return ;
			}
			redirect_heredoc(lst);
			redirect_outfile(lst, data);
			redirect_append(lst, data);
		}
		lst = lst->next;
	}
}
