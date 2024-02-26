/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 21:38:59 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/26 23:22:34 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param node node in linked list
 * @param cmd either unset or export
 * @brief puts custom error message on STDERR_FILENO
*/
void	put_custom_error(t_parser *node, char *str, char *cmd)
{
	if (mini_strcmp(cmd, "export") == 0)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		node->exit_code = E_GENERAL;
	}
	else if (mini_strcmp(cmd, "exit") == 0)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
		node->exit_code = E_GENERAL;
	}
}

/**
 * @param node node in linked list
 * @param cmd either unset or export
 * @brief puts custom error message on STDERR_FILENO
*/
void	put_execute_error(t_parser *node)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(node->proc->cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	node->exit_code = E_COMMAND_NOT_FOUND;
}

/**
 * @param node node in linked list
 * @param cmd either unset or export
 * @brief puts custom error message on STDERR_FILENO
*/
void	put_permission_error(t_parser *node)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(node->proc->cmd, STDERR_FILENO);
	ft_putstr_fd(": permission denied\n", STDERR_FILENO);
	node->exit_code = E_NO_PERMISSION;
}

/**
 * @param lst node in linked list
 * @brief puts custom error message on STDERR_FILENO
*/
void	no_such_file(char *str, t_parser *lst)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	lst->exit_code = E_GENERAL;
}

/**
 * @param error int errno given to exit
 * @brief provides correct error message and exits
*/
void	mini_error(int exit_enum, t_parser *lst)
{
	lst->exit_code = exit_enum;
}
