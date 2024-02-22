/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 21:38:59 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/22 21:20:00 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param node node in linked list
 * @param cmd either unset or export
 * @brief puts custom error message on STDERR_FILENO
 * @todo is index[0] okay?
*/
void	put_custom_error(t_parser *node, char *cmd)
{
	if (mini_strcmp(cmd, "export") == 0)
	{

		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(node->proc->str[0], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n",STDERR_FILENO);
		node->exit_code = EXIT_FAILURE;
	}
	else if (mini_strcmp(cmd, "exit") == 0)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(node->proc->str[0], STDERR_FILENO);
		ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
		node->exit_code = EXIT_FAILURE;
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
	dprintf(STDERR_FILENO, NO_SUCH_THING, str);
	lst->exit_code = EXIT_FAILURE;
}

/**
 * @param lst parser linked list
 * @brief provides correct error message after child process
 * @todo
 * too many functions in file
 * norm it
	// printf("SIG: %d\n", WTERMSIG(exit_num));
	// printf("EX: %d\n", WIFEXITED(exit_num));
	// printf("EXST: %d\n", WEXITSTATUS(exit_num));
*/
void	exit_status(t_parser *lst)
{
	int status;
	
	status = 0;
	
	if (WIFEXITED(status)) 
		lst->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status)) 
		lst->exit_code = 128 + WTERMSIG(status);
}

/**
 * @param error int errno given to exit
 * @brief provides correct error message and exits
 * @todo is this function okay? do I need to exit?
 * norm it
*/
void	mini_error(int exit_enum, t_parser *lst)
{
	lst->exit_code = exit_enum;
}
