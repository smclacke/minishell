/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/04 13:30:15 by dreijans      ########   odam.nl         */
/*                                                                            */
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
	t_expand	*exp;
	int			len;

	head = lst;
	exp = NULL;
	while (head)
	{
		if (head->str != NULL)
		{
			len = ft_strlen(head->str);
			if (ft_strnstr(head->str, "$", len))
			{
				exp = malloc(sizeof (t_expand));
				init_expand_struct(exp);
				exp_dollar(head, env, exp, len);
			}
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

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @param i index
 * @param len lenght of node->str
 * @brief checks if $ is at the end of the string
 * @return 1 if the $ is at the end of the string
 * 0 if not.
*/
int	check_at_len(t_parser *node, t_expand *exp, int i, int len)
{
	if (node->str[i] == '$' && (i + 1) == len)
	{
		free_remain_struct(exp);
		return (1);
	}
	return (0);
}

/**
 * @param node parser linked list
 * @param env environmet linked list
 * @brief checks for a $ sign in the node
 * expands the string to actual value
*/
void	exp_dollar(t_parser *node, t_env **env, t_expand *exp, int len)
{
	int			i;
	int			j;

	i = 0;
	while (node->str[i] != '\0')
	{
		if (check_at_len(node, exp, i, len) != 0)
			return ;
		else if (node->str[i] == '$' && (i + 1) != len)
		{
			get_before_dollar(node, exp, i);
			i++;
			j = i;
			get_compare_str(node, exp, i, j);
			if (get_check_value(exp, env) != 0)
				break ;
			free(exp->comp_str);
			reassing_before_dollar(exp);
			i = j - 1;
		}
		i++;
	}
	return_exp(node, exp);
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
