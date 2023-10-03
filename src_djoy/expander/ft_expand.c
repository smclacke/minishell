/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/03 13:18:43 by smclacke      ########   odam.nl         */
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
	// expand_dollar(node, env);//going to be here for now
	while (lst)
	{
		if (check_for_meta(lst))
		{
			printf("expander:		there's a meta whoop\n");
			printf("\n----------------------------------\n");
		}
		if (check_for_builtin(lst))
		{
			printf("expander: 		there's a builtin whoop\n");
			printf("\n----------------------------------\n");
			do_builtin(lst, env);
		}
		lst = lst->next;
	}
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
 * 1) if whats after $ can be linked to env print the value equivalent
 * 2) if there's something before the $ echo will print that
 * 3) if it's just a dollar echo will print it and the string that
 * comes after it.
 * maybe this can already be done in parser
*/
// void	expand_dollar(t_parser *node, t_env **env)
// {
// 	int		len;
// 	int		i;
// 	char	*before_dollar;
// 	char	*compare_str;
// 	char	*temp;

// 	len = ft_strlen(node->data->str);
// 	i = 0;
// 	before_dollar = NULL;
// 	compare_str = NULL;
// 	temp = NULL;
// 	while (node->data->str)
// 	{
// 		while (node->data->str[i] != '$')
// 		{
// 			i++;
// 			if (node->data->str[i] == '$' && i == len)
// 				return ;
// 		}
// 		before_dollar = ft_substr(node->data->str, 0, i);
// 		temp = node->data->str;
// 		node->data->str = before_dollar;
// 		free (temp);
// 		printf("node->data->str = [%s]\n", node->data->str);
// 		if (node->data->str[i] == '$' && i != len)
// 		{
// 			i++;
// 			compare_str = ft_substr(node->data->str, i, len - i);
// 			temp = node->data->str;
// 			node->data->str = compare_str;
// 			free (temp);
// 		}
// 		printf("node->data->str = [%s]\n", node->data->str);
// 	}
// 	/*
// 	1- loop through string save everything in temp until $
// 	2- if index of $ == len put that in temp too/ or return OG.
// 	3- if $ != len put rest in compare_string = ft_substr
// 	*/
// 	while (env[i])
// 	{
// 		if (mini_strcmp(node->data->str, &env->value, len - 1));
// 		//4-  if temp != NULL and if it finds anything str_join temp with env->value
// 		//5-  else replace node->date->str with expanded value from
// 		//env->value[i];

// 	}
// 	//6- if that doesnt return a value just return temp;
// 	//7- working? great make it work with quotes
// }


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
	if (!node)
		return (false);
	if (mini_strcmp(node->str, "$") == 0)
	{
		printf("expander:		dolllaaaah\n");
		//dollar_expand fucntion
		return (true);
	}
	else if (mini_strcmp(node->meta, ">>") == 0)
	{
		printf("expander:		Output Append\n");
		return (true);
	}
	else if (mini_strcmp(node->meta, "<<") == 0)
	{
		printf("expander:		here doc\n");
		return (true);
	}
	else if (mini_strcmp(node->meta, ">") == 0)
	{
		printf("expander:		output Redirect\n");
		return (true);
	}
	else if (mini_strcmp(node->meta, "<") == 0)
	{
		printf("expander:		Input Redirect\n");
		return (true);
	}
	else if (mini_strcmp(node->meta, "|") == 0)
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
	if (mini_strcmp(node->cmd, "exit") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "echo") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "cd") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "pwd") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "export") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "unset") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "env") == 0)
		return (true);
	else
		return (false);
}
