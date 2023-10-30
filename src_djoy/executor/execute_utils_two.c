/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 20:59:12 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/27 19:04:28 by dreijans      ########   odam.nl         */
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
 * @todo cat << EOF forked niet 
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
