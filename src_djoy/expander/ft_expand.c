/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/08 22:05:13 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../../include/djoyke.h"

// /* sarah parses the word i need to check if the word requires an action:
// "user" = user (word), "$user" = djoyke (action), '$user' = $user (word) */
// //>>
// //>

void	ft_expand(t_parser *lst)
{
	if (check_for_meta(lst))
		printf("expander:		there's a meta whoop\n");
	if (check_for_builtin(lst))
		printf("expander: 		there's a builtin whoop\n");
}

// // removing files int unlink(const char *pathname);
/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find meta_chars: 
 * $, >>, <<, >, <, |
 * @todo 
 * 1) needs to be passed to actual process,
 * 2) MAYBE MAKE IT A BOOL?
*/
bool	check_for_meta(t_parser *lst)
{
	if (lst->meta == NULL)
		return (false);
	if (mini_strcmp(lst->meta, "$") == 0)
	{
		printf("expander:		dolllaaaah\n");
		return (true);
	}
	else if (mini_strcmp(lst->meta, ">>") == 0)
	{
		printf("expander:		Output Append\n");
		return (true);
	}
	else if (mini_strcmp(lst->meta, "<<") == 0)
	{
		printf("expander:		here doc\n");
		return (true);
	}
	else if (mini_strcmp(lst->meta, ">") == 0)
	{
		printf("expander:		output Redirect\n");
		return (true);
	}
	else if (mini_strcmp(lst->meta, "<") == 0)
	{
		printf("expander:		Input Redirect\n");
		return (true);
	}
	else if (mini_strcmp(lst->meta, "|") == 0)
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
bool	check_for_builtin(t_parser *lst)
{
	if (lst->cmd == NULL)
		return (false);
	if (mini_strcmp(lst->cmd, "echo") == 0)
		return (true);
	else if (mini_strcmp(lst->cmd, "cd") == 0)
		return (true);
	else if (mini_strcmp(lst->cmd, "pwd") == 0)
		return (true);
	else if (mini_strcmp(lst->cmd, "export") == 0)
		return (true);
	else if (mini_strcmp(lst->cmd, "unset") == 0)
		return (true);
	else if (mini_strcmp(lst->cmd, "env") == 0)
		return (true);
	else if (mini_strcmp(lst->cmd, "exit") == 0)
		return (true);
	else
		return (false);
}
