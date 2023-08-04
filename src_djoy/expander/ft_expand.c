/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/04 14:16:39 by dreijans      ########   odam.nl         */
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

// /**
//  * @param lst linked list to loop through
//  * @brief loops to list to go to last position
// */
// t_expand	*shelly_expand_lstlast(t_expand *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

// /**
//  * @param lst linked list
//  * @param new new node to be added to linked list 
//  * @brief loops through list to add the new node to the back
//  * @todo adding previous in case of doubly linked list
// */
// void	shelly_expand_lstadd_back(t_expand **lst, t_expand *new)
// {
// 	t_expand	*last;

// 	if (*lst)
// 	{
// 		last = shelly_expand_lstlast(*lst);
// 		last->next = new;
// 	}
// 	else
// 		*lst = new;
// }

// t_expand	*init_expand_list(t_parser *lst)
// {
// 	t_expand	*new;

// 	new = (t_expand *)malloc(sizeof(*new));
// 	if (!new)
// 		micro_error("malloc", errno);
// 	if (lst->sign != NULL)
// 		new->sign = lst->sign;
// 	// else
// 	// 	new->sign = NULL;
// 	new->str = lst->str;
// 	if (shelly_check_for_builtin(lst))
// 		new->builtin = lst->cmd;
// 	else
// 		new->builtin = NULL;
// 	new->cmd = NULL;
// 	new->next = NULL;
// 	printf("new->str = [%s]\n", new->str);
// 	printf("new->sign = [%s]\n", new->sign);
// 	printf("new->builtin = [%s]\n", new->builtin);
// 	return (new);
// }

// /**
//  * @param envp environment pointer
//  * @param lst list with parsed tokens
//  * @brief makes expand list by checking the nodes parsed
//  * @todo 
//  * 1) do I need to do this in a loop? everything is now in one node
//  * 2) expand(mini->tokens) // tokens from s_parser struct, 
//  * 3) check built-in, check meta char, check quotes.
//  * 4) see if i need to fork, just execute or even redirect input output
// */
// t_expand	*micro_expand(t_parser *lst)
// {
// 	t_expand	*expand_node;
// 	t_expand	*expand_head;

// 	expand_node = NULL;
// 	expand_head = NULL;
// 	expand_node = init_expand_list(lst);
// 	shelly_expand_lstadd_back(&expand_head, expand_node);
// 	return (expand_head);
// }
