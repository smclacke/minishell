/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_expand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:20:06 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/02 13:55:00 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find meta_chars: 
 * $, >>, <<, >, <, |
 * @todo 
 * 1) needs to be passed to actual process,
 * 2) MAYBE MAKE IT A BOOL?
*/
bool	micro_check_for_meta(t_parser *node)
{
	if (micro_strcmp(node->sign, "$") == 0)
		return (true);
	else if (micro_strcmp(node->sign, ">>") == 0)
		return (true);
	else if (micro_strcmp(node->sign, "<<") == 0)
		return (true);
	else if (micro_strcmp(node->sign, ">") == 0)
		return (true);
	else if (micro_strcmp(node->sign, "<") == 0)
		return (true);
	else if (micro_strcmp(node->sign, "|") == 0)
		return (true);
	else
		return (false);
}

/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find built-ins: 
 * echo, cd, pwd, export, unset, env and exit
*/
bool	shelly_check_for_builtin(t_parser *node)
{
	if (micro_strcmp(node->cmd, "echo") == 0)
		return (true);
	else if (micro_strcmp(node->cmd, "cd") == 0)
		return (true);
	else if (micro_strcmp(node->cmd, "pwd") == 0)
		return (true);
	else if (micro_strcmp(node->cmd, "export") == 0)
		return (true);
	else if (micro_strcmp(node->cmd, "unset") == 0)
		return (true);
	else if (micro_strcmp(node->cmd, "env") == 0)
		return (true);
	else if (micro_strcmp(node->cmd, "exit") == 0)
		return (true);
	else
		return (false);
}

t_expand	*init_expand_list(t_parser *node)
{
	t_expand	*new;

	new = (t_expand *)malloc(sizeof(*new));
	if (!new)
		micro_error("malloc", errno);
	printf("node->cmd = [%s]\n", node->cmd);
	printf("node->str = [%s]\n", node->str);
	printf("node->sign = [%s]\n", node->sign);
	if (!micro_check_for_meta(node))
		new->sign = NULL;
	else
		new->sign = node->sign;
	printf("new->sign = [%s]\n", new->sign);
	new->str = node->str;
	if (shelly_check_for_builtin(node))
		new->builtin = node->cmd;
	else if (!shelly_check_for_builtin(node))
		new->builtin = NULL;
	printf("new->builtin = [%s]\n", new->builtin);
	new->next = NULL;
	return (new);
}
/**
 * @param lst linked list to loop through
 * @brief loops to list to go to last position
*/
t_expand	*shelly_expand_lstlast(t_expand *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/**
 * @param lst linked list
 * @param new new node to be added to linked list 
 * @brief loops through list to add the new node to the back
 * @todo adding previous in case of doubly linked list
*/
void	shelly_expand_lstadd_back(t_expand **lst, t_expand *new)
{
	t_expand	*last;

	if (*lst)
	{
		last = shelly_expand_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}


/* check for built ins, meta's pipes? to see if i need to fork, 
just execute or even redirect input output.*/
		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.

t_expand	*micro_expand(char **envp, t_parser *node)
{
	// t_env	    *env;
	t_expand	*expand;
	t_expand	**list;

	(void) envp;
	expand = NULL;
	list = NULL;
	// env = micro_env_list(envp);
	expand = init_expand_list(node);
	shelly_expand_lstadd_back(list, expand);
	return (*list);
}
