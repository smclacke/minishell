/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 20:51:29 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/01 16:58:16 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param lst parser linked list
 * @param data execute struct
 * @param exec executable
 * @brief checks executable
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
		exit(lst->exit_code);
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

/**
 * @param node node in linked list
 * @param cmd either unset or export
 * @brief puts custom error message on STDERR_FILENO
*/
void	put_exit_error(t_parser *node)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(node->proc->cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	node->exit_code = E_COMMAND_NOT_FOUND;
	exit(node->exit_code);
}

/**
 * @param node node in linked list
 * @param str either unset or export
 * @brief puts custom error message on STDERR_FILENO
*/
void	infile_permission_error(t_parser *node, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": permission denied\n", STDERR_FILENO);
	node->exit_code = E_NO_PERMISSION;
}

/**
 * @param node node in linked list
 * @param str either unset or export
 * @brief puts custom error message on STDERR_FILENO
*/
void	no_valid_command(t_parser *node, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": not a valid command\n", STDERR_FILENO);
	node->exit_code = E_GENERAL;
	exit(node->exit_code);
}
