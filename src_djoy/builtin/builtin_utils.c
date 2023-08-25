/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 15:47:58 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/25 15:51:07 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param env pointer to environment
 * @brief free's content plus node.
*/
void	free_all(t_env *env)
{
	free(env->value);
	free(env->key);
	free(env->full);
	free(env);
}

/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find built-ins: 
 * echo, cd, pwd, export, unset, env and exit
 * @return EXIT_FAILURE if no built-in was found
 * @todo 
 * 1) needs to be passed to actual process,
 * 2) exit(EXIT_FAILURE) is it really neccesary?
 * 3) MAYBE MAKE IT A BOOL?
 * 4) line 73: gives pwd not the entire path after unsetting
*/
void	do_builtin(t_parser *lst, t_env **env)
{
	if (mini_strcmp(lst->cmd, "echo") == 0)
		ft_echo(lst);
	if (mini_strcmp(lst->cmd, "cd") == 0)
		ft_cd(lst, env);
	if (mini_strcmp(lst->cmd, "pwd") == 0)
		ft_pwd();
	if (mini_strcmp(lst->cmd, "export") == 0)
		ft_export(lst, env);
	if (mini_strcmp(lst->cmd, "unset") == 0)
		ft_unset(lst, env);
	if (mini_strcmp(lst->cmd, "env") == 0)
		ft_env(*env);
}


