/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 21:38:59 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/19 18:49:29 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param node node in linked list
 * @param cmd either unset or export
 * @brief puts custom error message on STDOUT_FILENO
 * @todo is index[0] okay?
*/
void	put_custom_error(t_parser *node, char *cmd)
{
	if (mini_strcmp(cmd, "export") == 0)
	{
		ft_putstr_fd("minishell: export: `", STDOUT_FILENO);
		ft_putstr_fd(node->proc->str[0], STDOUT_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
	}
	else if (mini_strcmp(cmd, "exit") == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
		ft_putstr_fd(node->proc->str[0], STDOUT_FILENO);
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
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(node->proc->cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

/**
 * @param node node in linked list
 * @param cmd either unset or export
 * @brief puts custom error message on STDOUT_FILENO
*/
void	put_permission_error(t_parser *node)
{
	ft_putstr_fd(node->proc->cmd, STDERR_FILENO);
	ft_putstr_fd(": permission denied\n", STDERR_FILENO);
}

/**
 * @param lst node in linked list
 * @brief puts custom error message on STDOUT_FILENO
*/
void	no_such_file(char *str, t_parser *lst)
{
	dprintf(STDERR_FILENO, NO_SUCH_THING, str);
	mini_error(E_GENERAL, lst);
}

/**
 * @param error int errno given to exit
 * @brief provides correct error message and exits
 * @todo is this function okay? do I need to exit?
 * norm it
 * - not just for error, for passing exit codes? meh
	// exit(exit_enum);
*/
void	mini_error(int exit_enum, t_parser *lst)
{
	lst->exit_code = exit_enum;
}
