/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 21:24:07 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/23 23:08:24 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param lst parser linked list
 * @brief provides correct error message after child process
 * @todo
 * norm it
*/
void	exit_status(int status, t_parser *lst)
{
	if (WIFEXITED(status))
		lst->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		lst->exit_code = 128 + WTERMSIG(status);
	else
		return ;
}

/**
 * @param read_line string containing line read.
 * @param file int with file fd.
 * @param env environment linked list
 * @param file file fd
 * @brief writes to the heredoc frees the read_line
*/
void	write_to_file(t_parser *lst, char *readline, t_env **env, int file)
{
	if (lst && lst->hd_flag == 0)
	{
		if (ft_isdollar(readline))
			readline = hd_expand(env, readline);
	}
	if (readline)
	{
		write(file, readline, ft_strlen(readline));
		free(readline);
	}
	write(file, "\n", 1);
}

/**
 * @param lst node in linked list
 * @brief puts custom error message on STDERR_FILENO
*/
void	redir_file_error(char *str, t_parser *lst)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	lst->exit_code = E_GENERAL;
}

/**
 * @param lst node in linked list
 * @brief puts custom error message on STDERR_FILENO
*/
void	dir_error(char *str, t_parser *lst)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	lst->exit_code = E_GENERAL;
}

/**
 * @param lst node in linked list
 * @brief puts custom error message on STDERR_FILENO
*/
void	write_permission_error(char *str, t_parser *lst)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(" no writing permissions\n", STDERR_FILENO);
	lst->exit_code = E_GENERAL;
}
