/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 15:47:58 by dreijans      #+#    #+#                 */
/*   Updated: 2023/09/07 19:48:41 by dreijans      ########   odam.nl         */
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
 * 4) former line 73: gives pwd not the entire path after unsetting
*/
void	do_builtin(t_parser *node, t_env **env)
{
	if (!node->cmd_list->cmd)
		mini_error("parser", errno);
	else if (mini_strcmp(node->cmd_list->cmd, "echo") == 0)
		ft_echo(node);
	else if (mini_strcmp(node->cmd_list->cmd, "cd") == 0)
		ft_cd(node, env);
	else if (mini_strcmp(node->cmd_list->cmd, "pwd") == 0)
		ft_pwd();
	else if (mini_strcmp(node->cmd_list->cmd, "export") == 0)
		ft_export(node, env);
	else if (mini_strcmp(node->cmd_list->cmd, "unset") == 0)
		ft_unset(node, env);
	else if (mini_strcmp(node->cmd_list->cmd, "env") == 0)
		ft_env(*env);
	else if (mini_strcmp(node->cmd_list->cmd, "exit") == 0)
		ft_exit(node);
}

/**
 * @param node node in linked list
 * @brief checks if the words are export and unset norm
 * proof.
 * key (word) first letter has:
 * capital (H), lowercase (h), underscore (_) as first letter 
 * else give error if given 99=djoyke as key
 * minishell: export: `99=djoyke': not a valid identifier
 * rest of word can only have numbers, letters and underscore.
 * else give error export d@@=haha
 * minishell: export: `d@@=haha': not a valid identifier
 * same for unset
 * @return true if nothing wrong found with the words
 * @todo  
 * arg->cmd: export
 * arg->str: djoyke
 * arg->str: =gek
 * expander: 		there's a builtin whoop
 * 
 * minishell: export: `djoyke': not a valid identifier 
 * -->this thould be =gek instead.
 * 
 * strchr: Undefined error: 0 
 * ->this should not happen at all dont go further.
 * 
 * still need to do bracket check
 * for now looping because not actual parsed list
 * line 96: node containing string for now fix when parsing is fixed
 * bash-3.2$ export djoyke =gek
 * bash: export: `=gek': not a valid identifier
 * bash-3.2$ export djoyke="gek gggg" (two words if it's in quotations)
 * bash-3.2$ env
 * env part:
 * djoyke=gek gggg
 * bash-3.2$
*/
bool	word_check(t_parser *node)
{
	char	**words;
	char	*cmd;
	int		i;

	cmd = node->cmd_list->cmd;
	node = node->next;
	words = ft_split(node->cmd_list->strs, '=');
	if ((mini_strcmp(cmd, "unset") == 0) && words[1])
	{
		put_custom_error(node, cmd);
		return (true);
	}
	if (words == NULL)
		mini_error("malloc split", errno);
	if ((ft_isalpha(words[0][0]) == 0) && words[0][0] != '_')
	{
		put_custom_error(node, cmd);
		return (true);
	}
	i = 1;
	while (words[0][i])
	{
		if (words[0][i] != '_' && ft_isalnum(words[0][i]) == 0)
		{
			put_custom_error(node, cmd);
			return (true);
		}
		i++;
	}
	return (false);
}

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
		ft_putstr_fd(node->cmd_list->strs, STDOUT_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
	}
	else if (mini_strcmp(cmd, "unset") == 0)
	{
		ft_putstr_fd("minishell: unset: `", STDOUT_FILENO);
		ft_putstr_fd(node->cmd_list->strs, STDOUT_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
	}
	else if (mini_strcmp(cmd, "exit") == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
		ft_putstr_fd(node->cmd_list->strs, STDOUT_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
	}
}
