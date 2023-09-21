/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 15:47:58 by dreijans      #+#    #+#                 */
/*   Updated: 2023/09/21 18:15:03 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"
#include <limits.h>

#define ERROR_MESSAGE ": positive numeric argument 255 or below required\n"

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
	if (!node->data_type->cmd)
		mini_error("parser", errno);
	else if (mini_strcmp(node->data_type->cmd, "echo") == 0)
		ft_echo(node);
	else if (mini_strcmp(node->data_type->cmd, "cd") == 0)
		ft_cd(node, env);
	else if (mini_strcmp(node->data_type->cmd, "pwd") == 0)
		ft_pwd();
	else if (mini_strcmp(node->data_type->cmd, "export") == 0)
		ft_export(node, env);
	else if (mini_strcmp(node->data_type->cmd, "unset") == 0)
		ft_unset(node, env);
	else if (mini_strcmp(node->data_type->cmd, "env") == 0)
		ft_env(*env);
	else if (mini_strcmp(node->data_type->cmd, "exit") == 0)
		ft_exit(node);
}

/**
 * @param temp linked list
 * @param words 2D array with seperate words key and value
 * @param cmd string containing command
 * @brief checks if key and value are alphanumeric
 * @return 1 if not alphanumeric, 0 is alphanumeric
*/
int	key_value_check(t_parser *temp, char **words, char *cmd)
{
	int	i;

	if ((ft_isalpha(words[0][0]) == 0) && words[0][0] != '_')
	{
		put_custom_error(temp, cmd);
		return (1);
	}
	i = 1;
	while (words[0][i])
	{
		if (words[0][i] != '_' && ft_isalnum(words[0][i]) == 0)
		{
			put_custom_error(temp, cmd);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @param lst linked list
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
 * HANDLE QUOTES WHEN IT'S FIXED IN THE PARSER, you're doing great honey
 * bash-3.2$ export djoyke="gek gggg" (two words if it's in quotations)
 * bash-3.2$ env
 * env part:
 * djoyke=gek gggg
 * bash-3.2$
 * 2) export djoyke
 * will be added to environmet but not shown when doing env
 * becuase there's no value
 * but export will show it when you print declare -x; fix in env
*/
bool	word_check(t_parser *lst)
{
	t_parser	*temp;
	char		**words;
	char		*cmd;

	cmd = lst->data_type->cmd;
	temp = lst->next;
	words = ft_split(temp->data_type->strs, '=');
	if ((mini_strcmp(cmd, "unset") == 0) && words[1])
	{
		put_custom_error(temp, cmd);
		return (true);
	}
	if (words == NULL)
		mini_error("malloc split", errno);
	if (key_value_check(temp, words, cmd) == 1)
		return (true);
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
		ft_putstr_fd(node->data_type->strs, STDOUT_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
	}
	else if (mini_strcmp(cmd, "unset") == 0)
	{
		ft_putstr_fd("minishell: unset: `", STDOUT_FILENO);
		ft_putstr_fd(node->data_type->strs, STDOUT_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
	}
	else if (mini_strcmp(cmd, "exit") == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
		ft_putstr_fd(node->data_type->strs, STDOUT_FILENO);
		ft_putstr_fd(ERROR_MESSAGE, STDOUT_FILENO);
	}
}
