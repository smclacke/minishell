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
		check_for_meta(head);
		if (check_for_builtin(head))
			do_builtin(head, env);
		// if (check_for_meta(head))
		// {
		// 	printf("expander:		there's a meta whoop\n");
		// 	printf("\n----------------------------------\n");
		// }
		// if (check_for_builtin(head))
		// {
		// 	printf("expander: 		there's a builtin whoop\n");
		// 	printf("\n----------------------------------\n");
		// 	do_builtin(head, env);
		// }
		head = head->next;
	}
}

int	check_for_value(t_parser *node, char *str, char *str2, t_env **env)
{
	char	*temp;
	char	*new_str;
	t_env	*head;

	temp = NULL;
	new_str = NULL;
	head = *env;
	while (head)
	{
		if (mini_strcmp(str, head->key) == 0)
		{
			temp = str;
			str = ft_substr(head->value, 0, ft_strlen(head->value));//it leaks here 9 bytes check later
			free_str(temp);
			new_str = ft_strjoin(str2, str);//it leaks here 13 bytes 1 ovject check later
			temp = node->data->str;
			node->data->str = new_str;
			printf("new_str = [%s]\n", node->data->str);
			free_str(temp);
			free_str(new_str);
			free_str(str);
			return (1);
		}
		else
			head = head->next;
	}
	return (0);
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

*/
void	expand_dollar(t_parser *node, t_env **env, int len)
{
	int			i;
	char		*before_dollar;
	char		*compare_str;
	char		*temp;

	i = 0;
	before_dollar = NULL;
	compare_str = NULL;
	temp = NULL;
	while (node->data->str[i] != '\0')
	{
		if (node->data->str[i] == '$' && i == (len - 1))
			return ;
		else if (node->data->str[i] == '$' && i != len)
		{
			before_dollar = ft_substr(node->data->str, 0, i);//leaks here 5 bytes 1 object check later
			i++;
			compare_str = ft_substr(node->data->str, i, len - i);//leaks here 5 bytes 1 obtject check later
			printf("compare_str = [%s]\n", compare_str);
			printf("before_dollar = [%s]\n", before_dollar);
			if (check_for_value(node, compare_str, before_dollar, env) == 0)
			{
				temp = node->data->str;
				// printf("temp = [%s]\n", temp);
				printf("1 node->data->str = [%s]\n", node->data->str);
				node->data->str = before_dollar; //segfaults here when the expanded string no existy
				printf("2 node->data->str = [%s]\n", node->data->str);
				free_str(temp);
			}
			free_str(before_dollar);
			printf("node->data->str = [%s]\n", node->data->str);
		}
		i++;
	}
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
