/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 20:59:12 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/01 20:05:51 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param lst parser linked list
 * @param env  environment linked list
 * @param data execute struct
 * @brief checks for single builtin command and if there are redirects
 * executes the builtin and redirect function
 * https://mariadb.com/kb/en/operating-system-error-codes/
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
				if (redirect(lst, data) == false)
					return (true);
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
*/
void	init_fork(t_parser *lst, t_env **env, t_execute *data)
{
	data->fork_pid = fork();
	handle_signals(CHILD);
	if (data->fork_pid == -1)
		lst->exit_code = E_GENERAL;
	if (data->fork_pid == 0)
		mini_forks(lst, env, data);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
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
 * @note keeping hd_count check since func used much, i.e. mini_forks
 * 		- when used with multi procs, check hd stuff...
 * redirect_heredoc: check if bool and return etc
*/
bool	redirect(t_parser *lst, t_execute *data)
{
	int	i;

	i = 0;
	while (i < lst->proc->red_count)
	{
		if (ft_strncmp(lst->proc->redir[i], ">", 2) == 0)
			if (redirect_outfile(lst->proc->redir[i + 1], data, lst) == false)
				return (false);
		if (ft_strncmp(lst->proc->redir[i], "<", 2) == 0)
			if (redirect_infile(lst->proc->redir[i + 1], data, lst) == false)
				return (false);
		if (ft_strncmp(lst->proc->redir[i], ">>", 3) == 0)
			if (redirect_append(lst->proc->redir[i + 1], data, lst) == false)
				return (false);
		i += 2;
	}
	i++;
	if (lst->proc->hd_last)
		redirect_heredoc(lst);
	return (true);
}
