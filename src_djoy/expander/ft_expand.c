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
 dreijans@f0r2s14:~/Documents/rank3$ echo $
$
dreijans@f0r2s14:~/Documents/rank3$ echo $USER
dreijans
dreijans@f0r2s14:~/Documents/rank3$ 

*/
void	ft_expand(t_parser *lst, t_env **env)
{
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
	/*
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
*/
bool	check_for_meta(t_parser *node)
{
	if (node->data == NULL)
		return (false);
	if (mini_strcmp(node->data->cmd, "$") == 0)
	{
		printf("expander:		dolllaaaah\n");
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
 * @todo everything needs to be in either str or cmd not 2 diff
 * thing!!
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
