/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_expand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:20:06 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/01 13:48:24 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* check for built ins, meta's pipes? to see if i need to fork, 
just execute or even redirect input output.*/
		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.

t_expand	*micro_expand(char **envp, t_parser *node)
{
	// t_env	    *env;
    t_expand    *expand;

    (void) envp;
	expand = NULL;
	// env = micro_env_list(envp);
	while (node)
	{
        shelly_expand_lstadd_back(&expand, init_expand_list(node));
	}
	return (expand);
}


/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find meta_chars: 
 * $, >>, <<, >, <, |
 * @todo 
 * 1) needs to be passed to actual process,
 * 2) MAYBE MAKE IT A BOOL?
*/
char	*micro_check_for_meta(t_parser *node)
{
	if (ft_strnstr(node->sign, "$", ft_strlen(node->sign)) == 0)
		return(node->sign);
	if (ft_strnstr(node->sign, ">>", ft_strlen(node->sign)) == 0)
		return(node->sign);
    if (ft_strnstr(node->sign, "<<", ft_strlen(node->sign)) == 0)
        return(node->sign);
	if (ft_strnstr(node->sign, ">", ft_strlen(node->sign)) == 0)
		return(node->sign);
    if (ft_strnstr(node->sign, "<", ft_strlen(node->sign)) == 0)
        return(node->sign);
	if (ft_strnstr(node->sign, "|", ft_strlen(node->sign)) == 0)
		return(node->sign);
	else
		return (NULL);
}

/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find built-ins: 
 * echo, cd, pwd, export, unset, env and exit
*/
char	*shelly_check_for_builtin(t_parser *node)
{
	if (ft_strcmp(node->cmd, "echo") == 0)
		return (node->cmd);
	if (ft_strcmp(node->cmd, "cd") == 0)
		return (node->cmd);
	if (ft_strcmp(node->cmd, "pwd") == 0)
		return (node->cmd);
	if (ft_strcmp(node->cmd, "export") == 0)
		return (node->cmd);
	if (ft_strcmp(node->cmd, "unset") == 0)
		return (node->cmd);
	if (ft_strcmp(node->cmd, "env") == 0)
		return (node->cmd);
	if (ft_strcmp(node->cmd, "exit") == 0)
		return (node->cmd);
	else
		return (NULL);
}

t_expand *init_expand_list(t_parser *node)
{
    t_expand *new;

    new = (t_expand *)malloc(sizeof(* new));
    if (!new)
        micro_error("malloc", errno);
    new->sign = micro_check_for_meta(node);
    new->str = node->str;
    new->builtin = shelly_check_for_builtin(node);
    new->next = NULL;
	// printf("expand sign is; %s\n", new->sign);
	return (new);
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