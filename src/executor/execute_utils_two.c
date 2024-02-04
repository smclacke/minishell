/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 20:59:12 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/04 20:07:43 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param lst parser linked list
 * @param env  environment linked list
 * @param data execute struct
 * @brief checks for single builtin command and if there are redirects
 * executes the builtin and redirect function
 * @note change to count == one because won't ever be 0 processes
 * 		1 == one process
*/
bool	single_builtin_cmd(t_parser *lst, t_env **env, t_execute *data)
{
	int	count;
	int	cmd_type;

	count = lst->proc->proc_count;
	cmd_type = 0;
	if (count == 1)
	{
		if (lst->proc->red_count != 0)
		{
			redirect(lst, data);
			if (data->error == false)
				return (true);
		}
		cmd_type = check_for_builtin(lst);
		if (cmd_type)
			do_builtin(lst, env, cmd_type);
		return (true);
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
 * @todo add list->proc-count instead of lst->n_cmd,
 * dont need to use int count anymore :)
 * check with if work :)
*/
void	pipeline(t_parser *lst, t_env **env, t_execute *data)
{
	int	count;
	int	i;

	count = lst->proc_count;//instead of this go to proc-count
	i = 0;
	while (lst)
	{
		if (count >= 1 && lst->proc_count)	
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
 * @todo remove printf statement check line 118
 * @note keeping hd_count check since func used much, i.e. mini_forks
 * 		- when used with multi procs, check hd stuff...
 * @note from single_builtin_cmd, already checked for redirs
 * 		make sure this happens on every redirect() call
	
	// redirs are totally separate from hd
	// if (!lst->proc->hd_count)
	// 	lst = lst->next; // don't list next, look only at current proc
*/
void	redirect(t_parser *lst, t_execute *data)
{
	if (!redirect_infile(lst->proc, data))
	{
		data->error = false;
		return ;
	}
	redirect_heredoc(lst->proc);
	redirect_outfile(lst->proc, data);
	redirect_append(lst->proc, data);
}
