/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_expand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:20:06 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/01 11:26:18 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* check for built ins, meta's pipes? to see if i need to fork, 
just execute or even redirect input output.*/
		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.

t_parser	*micro_expand(char **envp, t_parser *node)
{
	// t_env	    *env;
    t_expand    *expand;

    (void) envp;
	// env = micro_env_list(envp);
	while (node)
	{
        expand = init_expand_list(node);
		// micro_check_for_builtin(node, env);
        // printf("expand sign is; %s\n", expand->sign);
	}
	return (node);
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
		return("$");
	if (ft_strnstr(node->sign, ">>", ft_strlen(node->sign)) == 0)
		return(">>");
    if (ft_strnstr(node->sign, "<<", ft_strlen(node->sign)) == 0)
        return("<<");
	if (ft_strnstr(node->sign, ">", ft_strlen(node->sign)) == 0)
		return(">");
    if (ft_strnstr(node->sign, "<", ft_strlen(node->sign)) == 0)
        return("<");
	if (ft_strnstr(node->sign, "|", ft_strlen(node->sign)) == 0)
		return("|");
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
    new->str = NULL;
    new->builtin = NULL;
    new->next = NULL;
	printf("expand sign is; %s\n", new->sign);
	return (new);
}