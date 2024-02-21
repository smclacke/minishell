/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 21:38:59 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/21 17:04:15 by dreijans      ########   odam.nl         */
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
	}
	else if (mini_strcmp(cmd, "exit") == 0)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(node->proc->str[0], STDERR_FILENO);
		ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
		// mini_error(EXIT_FAILLURE, node);
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
	mini_error(E_COMMAND_NOT_FOUND, node);
	// node->exit_code = E_COMMAND_NOT_FOUND;
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
	// mini_error(E_NO_PERMISSION, node);
	node->exit_code = E_NO_PERMISSION;
}

/**
 * @param lst node in linked list
 * @brief puts custom error message on STDERR_FILENO
*/
void	no_such_file(char *str, t_parser *lst)
{
	dprintf(STDERR_FILENO, NO_SUCH_THING, str);
	// mini_error(E_GENERAL, lst);
	lst->exit_code = EXIT_FAILURE;
	
}

/**
 * @param error int errno given to exit
 * @brief provides correct error message and exits
 * @todo is this function okay? do I need to exit?
 * norm it
 * - not just for error, for passing exit codes? meh
	// exit(exit_enum);
	change the name to exit_status_hub
*/
// void	mini_error(t_parser *lst)
void	mini_error(int exit_num, t_parser *lst)
{
		// else if (all->here_status == 256)
		// g_exit_status = 1;
	// int stat = 0;
	
	printf("SIG: %d\n", WTERMSIG(exit_num));
	printf("EX: %d\n", WIFEXITED(exit_num));
	printf("EXST: %d\n", WEXITSTATUS(exit_num));
	if (WTERMSIG(exit_num) == 2 || WTERMSIG(exit_num) == 3)
		lst->exit_code = WTERMSIG(exit_num) + 128;
	else if (WIFEXITED(exit_num))
		lst->exit_code = WEXITSTATUS(exit_num);
	else
		lst->exit_code = exit_num;
}
