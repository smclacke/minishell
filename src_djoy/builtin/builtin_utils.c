/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 15:47:58 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/25 16:03:27 by dreijans      ########   odam.nl         */
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
 * @param node node in linked list
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
void	do_builtin(t_parser *node, t_env **env)
{
	if (mini_strcmp(node->cmd, "echo") == 0)
		ft_echo(node);
	if (mini_strcmp(node->cmd, "cd") == 0)
		ft_cd(node, env);
	if (mini_strcmp(node->cmd, "pwd") == 0)
		ft_pwd();
	if (mini_strcmp(node->cmd, "export") == 0)
		ft_export(node, env);
	if (mini_strcmp(node->cmd, "unset") == 0)
		ft_unset(node, env);
	if (mini_strcmp(node->cmd, "env") == 0)
		ft_env(*env);
}

void	word_check(t_parser *node)
{
	split_word = (node->str);
}

/* make function for unset and export checking if 
key (word) has:
	 capital (H), lowercase (h), underscore (_) as first letter 
else give error if given 99= as key
	 bash: export: `99=': not a valid identifier
	 rest of word can only have numbers, letters and underscore.
else give error export d@@=haha
	bash: export: `d@@=haha': not a valid identifier
same for unset */
