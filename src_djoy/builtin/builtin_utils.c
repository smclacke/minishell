/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 15:47:58 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/25 18:11:45 by dreijans      ########   odam.nl         */
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
 * ---> Djoyke Made!
Gutentag Fräulein Shelly, wie geht's?export djoyke =gek
iterations [0]
iterations [1]
iterations [2]
arg->cmd: export
arg->str: djoyke
arg->str: =gek
expander: 		there's a builtin whoop
strchr: Undefined error: 0
➜  new_mini git:(djoyke) ✗ make djoyke
 ---> Djoyke Made!
Gutentag Fräulein Shelly, wie geht's?export djoyke =gek
iterations [0]
iterations [1]
iterations [2]
arg->cmd: export
arg->str: djoyke
arg->str: =gek
expander: 		there's a builtin whoop
minishell: export: `djoyke': not a valid identifier
strchr: Undefined error: 0
➜  new_mini git:(djoyke) ✗ make djoyke
 ---> Djoyke Made!
Gutentag Fräulein Shelly, wie geht's?export djoyke=gek
iterations [0]
iterations [1]
arg->cmd: export
arg->str: djoyke=gek
expander: 		there's a builtin whoop
minishell: export: `djoyke=gek': not a valid identifier
Gutentag Fräulein Shelly, wie geht's?en
*/
bool	word_check(t_parser *node)
{
	char	**words;
	char	*cmd;
	int		i;

	i = 0;
	cmd = node->cmd;
	node = node->next;
	words = ft_split(node->str, '=');
	if (words == NULL)
		mini_error("malloc", errno);
	if (ft_isalpha(words[0][i]) == 0 && words[0][i] != '_')
	{
		put_custom_error(node, cmd);
		return (false);
	}
	i = 1;
	while (words[0][i])
	{
		if (words[0][i] != '_' && ft_isalnum(words[0][i]) != 0)
			return (false);
		i++;
	}
	//spaces check returns second word need to make it still tho
	//bash-3.2$ unset djoyke =gek
	//bash-3.2$ export djoyke*=haha
	//bash: export: `djoyke*=haha': not a valid identifier
	//bracket check
	return (true);
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
		ft_putstr_fd(node->str, STDOUT_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
	}
	else if (mini_strcmp(cmd, "unset") == 0)
	{
		ft_putstr_fd("minishell: unset: `", STDOUT_FILENO);
		ft_putstr_fd(node->str, STDOUT_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
	}
}
// bash: export: `9h=haha': not a valid identifier (working)

// bash-3.2$ unset 999
// bash-3.2$ export djoyke =gek
// bash: export: `=gek': not a valid identifier

// bash-3.2$ export djoyke=gek gggg (working)
// bash-3.2$ env (working)
// djoyke=gek (working)

// bash-3.2$ export djoyke="gek gggg" (two words if it's in quotations)
// bash-3.2$ env
// env part:
// djoyke=gek gggg
// bash-3.2$

// bash-3.2$ export djoyke= gek (working)
// bash-3.2$ env (working)
// djoyke= (working)