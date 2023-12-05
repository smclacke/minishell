/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 21:38:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/05 15:17:31 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param node node in linked list
 * @param cmd either unset or export
 * @brief puts custom error message on STDOUT_FILENO
*/
void	put_custom_error(t_parser *node, char *cmd)
{
	if (mini_strcmp(cmd, "export") == 0)
	{
		ft_putstr_fd("minishell: export: `", STDOUT_FILENO);
		ft_putstr_fd(node->str, STDOUT_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
	}
	else if (mini_strcmp(cmd, "unset") == 0)
	{
		ft_putstr_fd("minishell: unset: `", STDOUT_FILENO);
		ft_putstr_fd(node->str, STDOUT_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
	}
	else if (mini_strcmp(cmd, "exit") == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
		ft_putstr_fd(node->str, STDOUT_FILENO);
		ft_putstr_fd(ERROR_MESSAGE, STDOUT_FILENO);
	}
}

/**
 * @param node node in linked list
 * @param cmd either unset or export
 * @brief puts custom error message on STDOUT_FILENO
*/
void	put_execute_error(t_parser *node)
{
	ft_putstr_fd(node->cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

/**
 * @param node node in linked list
 * @param cmd either unset or export
 * @brief puts custom error message on STDOUT_FILENO
*/
void	put_permission_error(t_parser *node)
{
	ft_putstr_fd(node->cmd, STDERR_FILENO);
	ft_putstr_fd(": permission denied\n", STDERR_FILENO);
}

/**
 * @param lst node in linked list
 * @brief puts custom error message on STDOUT_FILENO
*/
void	no_such_file(t_parser *lst)
{
	dprintf(STDERR_FILENO, NO_SUCH_THING, lst->str);
	mini_error("", E_MALLOC, lst);
}

/**
 * @param string argument given to perror
 * @param error int errno given to exit
 * @brief provides correct error message and exits
 * @todo is this function okay?
*/
void	mini_error(char *error, int exit_enum, t_parser *lst)
{
	ft_putstr(error);
	lst->exit_code = exit_enum;
}
