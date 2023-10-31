/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 20:59:12 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/31 19:01:41 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

#define INFILE_ERROR "minishell: %s: No such file or directory\n"

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
	printf("count = %i\n", count);
	if (count == 1 && check_for_builtin(lst))
	{
		redirect(lst, data);
		do_builtin(lst, env);
		return (true);
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
	if (data->fork_pid == -1)
		mini_error("fork", errno);
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
 * @brief child execution process,  calls init_pipes
 * init_forks and close_between in a while loop
*/
void	child_builtin_cmd(t_parser *lst, t_env **env, t_execute *data)
{
	int	count;
	int	i;

	count = lst->n_cmd;
	i = 0;
	while (lst)
	{
		if (count >= 1 && lst->cmd)
		{
			init_pipe(i, count, data);
			init_fork(lst, env, data);
			close_between(data);
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
			redirect_append(lst, data);
		}
		lst = lst->next;
	}
}
