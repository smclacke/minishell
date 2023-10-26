/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 20:59:12 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/25 18:39:58 by dreijans      ########   odam.nl         */
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
		printf("hello??\n");
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
 * @todo input like only hi segfaults
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
			printf("hello there again\n");
			init_pipe(i, count, data);
			init_fork(lst, env, data);
			close_between(data);
			count--;
			i++;
		}
		lst = lst->next;
	}
}
// ==62364==ERROR: LeakSanitizer: detected memory leaks

// Direct leak of 7 byte(s) in 2 object(s) allocated from:
//     #0 0x49a26d in malloc (/home/dreijans/Documents/rank3/minishell/djoyke+0x49a26d)
//     #1 0x7fd7511aebac in xmalloc (/lib/x86_64-linux-gnu/libreadline.so.8+0x39bac)

// SUMMARY: AddressSanitizer: 7 byte(s) leaked in 2 allocation(s).
void	check_str_for_file(t_parser *node, t_execute *data)
{
	struct stat	file_stat;
	char	*str;

	if (mini_strcmp(node->cmd, "cat") == 0)
	{
		node = node->next;
		str = node->str;
		// node = node->next;
		if (data->hdoc_fd != -1)
		{
			str = "heredoc1";
		}
		if (access(str, F_OK) != 0)
			dprintf(STDERR_FILENO, INFILE_ERROR, node->str);
		if (stat(str, &file_stat) == 0)
		{
			if (S_ISREG(file_stat.st_mode))
			{
				data->hdoc_fd = open(str, O_RDWR, 0644);
				if (data->hdoc_fd == -1)
					mini_error("open infile", errno);
				if (dup2(data->hdoc_fd, STDIN_FILENO) == 0)
					close(data->hdoc_fd);
			}
			if (S_ISDIR(file_stat.st_mode))
				dprintf(STDERR_FILENO, "[%s] is a directory\n", str);
			else if (!S_ISDIR(file_stat.st_mode) && !S_ISREG(file_stat.st_mode))
				dprintf(STDERR_FILENO, "its not a file or directory\n");
		}
	}
}
