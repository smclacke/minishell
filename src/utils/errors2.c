/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 21:24:07 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/01 21:51:09 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param lst parser linked list
 * @brief provides correct error message after child process
*/
void	exit_status(int status, t_parser *lst)
{
	if (WIFEXITED(status))
		lst->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		lst->exit_code = 128 + WTERMSIG(status);
	return ;
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
bool	dir_error(char *str, t_parser *lst)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	lst->exit_code = E_GENERAL;
	return (false);
}

/**
 * @param lst node in linked list
 * @brief puts custom error message on STDERR_FILENO
*/
void	write_permission_error(char *str, t_parser *lst)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": No writing permissions\n", STDERR_FILENO);
	lst->exit_code = E_GENERAL;
}

bool	redir_error(t_parser *lst, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	lst->exit_code = errno;
	return (false);
}
