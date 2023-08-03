/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_expand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:20:06 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/03 17:28:50 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find built-ins: 
 * echo, cd, pwd, export, unset, env and exit
*/
bool	shelly_check_for_builtin(t_parser *lst)
{
	if (lst->cmd == NULL)
		return (false);
	if (micro_strcmp(lst->cmd, "echo") == 0)
		return (true);
	else if (micro_strcmp(lst->cmd, "cd") == 0)
		return (true);
	else if (micro_strcmp(lst->cmd, "pwd") == 0)
		return (true);
	else if (micro_strcmp(lst->cmd, "export") == 0)
		return (true);
	else if (micro_strcmp(lst->cmd, "unset") == 0)
		return (true);
	else if (micro_strcmp(lst->cmd, "env") == 0)
		return (true);
	else if (micro_strcmp(lst->cmd, "exit") == 0)
		return (true);
	else
		return (false);
}
