/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/09/22 19:00:18 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param lst linked list from parser
 * @brief checks if there's a meta or a builtin
 * sarah parses the word i need to check if the word requires an action:
 * "user" = user (word), "$user" = djoyke (action), '$user' = $user (word)
 * >>
 * >
 * @todo
 * bash-3.2$ cat $djoyke
 * cat: haaa: No such file or directory
 * cat: ggg: No such file or directory (is moeilijk maybe not)
 * 		cat $USER
 * 
 * 		char ** =	[0] cat
 * 					[1] $USER
 * 					[2] NULL
 * 
 * 		expanding handles [1]$USER (could be djoyke etc or nothing)
 * 		if it's nothing char ** after expanding should look like
 * 
 * 		char ** = [0] cat
 * 		[1] NULL
 *		give that to execve
 *		
 *		or:
 * 		
 *		char ** = [0] cat
 *				  [1] djoyke
 *				  [2] NULL
 *
 * 		[1] $USER get's removed not overwritten! (memcpy)
 * 		[2] NULL get's moved up!
 * 		
 * 		➜  ~ echo $USER
 * 		dreijans
 * 		➜  ~ echo $?
 * 		0	
 * 		➜  ~ echo ${USER}
 * 		dreijans
 * 		➜  ~ echo $?
 * 		0
 * 		➜  ~ echo "$USER"
 * 		dreijans
 * 		➜  ~ echo $?
 * 		0
 * 		➜  ~
 * 
 * 		bash-3.2$ echo hi > outfile
 * 		bash-3.2$ cat outfile
 * 		hi
 * 			
 * builtin needs to be redirected to outfile
 * does this mean that if a process ended correctly 
 * it needs to return 0? as in EXIT_SUCCESS?
 * if >>$USER no expanding user it's a delimiter now
*/
void	ft_expand(t_parser *lst, t_env **env)
{
	t_parser	*head;
	int			len;

	head = lst;
	while (head)
	{
		if (head->data->str != NULL)
		{
			len = ft_strlen(head->data->str);
			if (ft_strnstr(head->data->str, "$", len))
				expand_dollar(head, env, len);
		}
		head = head->next;
	}
	head = lst;
	while (head)
	{
		check_for_meta(head);
		if (check_for_builtin(head))
			do_builtin(head, env);
		head = head->next;
	}
}

char	*check_for_value(char *comp, t_env **env)
{
	char	*temp;
	char	*new_str;
	t_env	*head;

	temp = NULL;
	new_str = NULL;
	head = *env;
	while (head)
	{
		if (mini_strcmp(comp, head->key) == 0)
		{
			new_str = ft_substr(head->value, 0, ft_strlen(head->value));
			return (new_str);
		}
		else
			head = head->next;
	}
	return (NULL);
}

/**
 * @param node parser linked list
 * @param env environmet linked list
 * @brief checks for a $ sign in the node
 * @todo
 * echo $
 * $
 * -----------------
 * echo $USER
 * dreijans
 * -----------------
 * echo abc$USER
 * abcdreijans
* -----------------
 * echo abc$i
 * abc
 * -----------------
 * echo abc$
 * abc$
 * -----------------
 * echo a$bc
 * a
 * -----------------
 * echo $ USER
 * $ USER
 * ----------------
 * echo $USER$USER
 * dreijansdreijans
*/
void	expand_dollar(t_parser *node, t_env **env, int len)
{
	int			i;
	int			j;
	char		*before_dollar;
	char		*value;
	char		*compare_str;
	char		*new_str;

	i = 0;
	before_dollar = NULL;
	compare_str = NULL;
	new_str = NULL;
	while (node->data->str[i] != '\0')
	{
		if (node->data->str[i] == '$' && (i + 1) == len)
			return ;
		else if (node->data->str[i] == '$' && (i + 1) != len)
		{
			before_dollar = ft_substr(node->data->str, 0, i);
			printf("before_dolor = [%s]\n", before_dollar);
			i++;
			// find length of key(after $, stop on next dolaar. TODO: put in other function)
			j = i;
			while (node->data->str[j] != '$' && node->data->str[j] != '\0')
				j++;
			compare_str = ft_substr(node->data->str, i, j - i);
			printf("compare_str = [%s]\n", compare_str);
			// 1: split up into before the variable, the variable key, and after the variable.
			// 2: find the variable, if nothing, just return empty string(MALLOCED LIKE THE REST)
			// 3: glue before, the variable value, and after back together
			// 4: 
			// if (check_for_value(node, compare_str, env) == 0) new function char functie 
			value = check_for_value(compare_str, env);
			printf("value = [%s]\n", value);
			new_str = ft_strjoin(before_dollar, value);
			printf("new_str = [%s]\n", new_str);
			//go throuhg the loop again to find something else to expand! like abc$USER$USER
			// i--; //zet terug naar char before expanding $ sing
			i = j;
			//find a way to put after i in value again and join it with new_str before assigning to node->data->str
// 			 !_-(_|\echo abc$USER$USER
// [0]      cmd = echo     file = (null)   meta = (null)   str = (null)
// [1]      cmd = (null)   file = (null)   meta = (null)   str = abc$USER$USER
// before_dolor = [abc]
// compare_str = [USER]
// value = [dreijans]
// new_str = [abcdreijans]
// i = [8]
// before_dolor = [abc$USER]
// compare_str = [USER]
// value = [dreijans]
// new_str = [abc$USERdreijans]
// i = [13]
// abc$USER$USER  
			printf("i = [%i]\n", i);
			continue ;
		}
		i++;
	}
	if (compare_str != NULL)
		free_str(compare_str);
	if (before_dollar != NULL)
		free_str(before_dollar);
}


/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find meta_chars: 
 * $, >>, <<, >, <, |
 * @todo 
 * 1) needs to be passed to actual process,
 * 2) MAYBE MAKE IT A BOOL?
 * 3) removing files int unlink(const char *pathname);
	// while (lst)
	// {
	// 	if (lst->cmd)
	// 	{
	// 		check if $ expansion needed?
	// 		(check in the environment for USER and return whats after the = sign)
	// 			yes?
	// 				start expanding
	// 				if ($?)
	// 				{
	// 					expand to check the exit code
	// 				}
	// 	}
*/
bool	check_for_meta(t_parser *node)
{
	if (node->data == NULL)
		return (false);
	if (mini_strcmp(node->data->str, "$") == 0)
	{
		printf("expander:		dolllaaaah\n");
		//dollar_expand fucntion
		return (true);
	}
	else if (mini_strcmp(node->data->meta, ">>") == 0)
	{
		printf("expander:		Output Append\n");
		return (true);
	}
	else if (mini_strcmp(node->data->meta, "<<") == 0)
	{
		printf("expander:		here doc\n");
		return (true);
	}
	else if (mini_strcmp(node->data->meta, ">") == 0)
	{
		printf("expander:		output Redirect\n");
		return (true);
	}
	else if (mini_strcmp(node->data->meta, "<") == 0)
	{
		printf("expander:		Input Redirect\n");
		return (true);
	}
	else if (mini_strcmp(node->data->meta, "|") == 0)
	{
		printf("expander:		pipe\n");
		return (true);
	}
	else
		return (false);
}

/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find built-ins: 
 * echo, cd, pwd, export, unset, env and exit
*/
bool	check_for_builtin(t_parser *node)
{
	if (!node)
		return (false);
	if (mini_strcmp(node->data->cmd, "exit") == 0)
		return (true);
	else if (mini_strcmp(node->data->cmd, "echo") == 0)
		return (true);
	else if (mini_strcmp(node->data->cmd, "cd") == 0)
		return (true);
	else if (mini_strcmp(node->data->cmd, "pwd") == 0)
		return (true);
	else if (mini_strcmp(node->data->cmd, "export") == 0)
		return (true);
	else if (mini_strcmp(node->data->cmd, "unset") == 0)
		return (true);
	else if (mini_strcmp(node->data->cmd, "env") == 0)
		return (true);
	else
		return (false);
}
