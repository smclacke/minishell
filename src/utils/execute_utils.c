/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 20:51:29 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/26 23:40:16 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param lst parser linked list
 * @param data execute struct
 * @param exec executable
 * @brief checks executable
 * @todo check return error
*/
void	executable_check(t_parser *lst, t_execute *data, char *exec)
{
	if (exec == NULL)
	{
		if (lst->proc->cmd != NULL)
		{
			put_execute_error(lst);
			exit(lst->exit_code);
		}
		exit(lst->exit_code);
	}
	if (data->error == false)
		exit (lst->exit_code);
	if (access(exec, X_OK) == -1)
	{
		put_permission_error(lst);
		exit(lst->exit_code);
	}
}

/**
 * @param read_line string containing line read.
 * @param file int with file fd.
 * @param env environment linked list
 * @param file file fd
 * @brief writes to the heredoc frees the read_line
*/
void	write_to_file(t_parser *lst, char *rl, t_env **env, int file)
{
	if (lst && lst->hd_flag == 0)
	{
		if (ft_isdollar(rl))
			rl = hd_expand(env, rl);
	}
	if (rl)
	{
		write(file, rl, ft_strlen(rl));
		free(rl);
	}
	write(file, "\n", 1);
}
