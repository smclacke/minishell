/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 21:38:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/30 18:25:53 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

#define ERROR_MESSAGE ": positive numeric argument 255 or below required\n"

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
 * @param o_d char string containing old working dir
 * @brief puts custom error message on STDOUT_FILENO
 * frees o_d and exits.
 * @todo do i need to say that it doesnt exist
*/
void	no_such_file(t_parser *lst)
{
	char	*error;

	error = ft_strjoin("minishell: cd: ", lst->str);
	mini_error(error, errno);
}
