/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_expand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:20:06 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/31 21:28:09 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* check for built ins, meta's pipes? to see if i need to fork, 
just execute or even redirect input output.*/
		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.

t_parser	*micro_expand(char **envp, t_parser *node)
{
	t_env	*env;

	env = micro_env_list(envp);
	while (node)
	{
        init_expand_list(NULL);
		micro_check_for_builtin(node, env);
		micro_check_for_meta(node, env);
	}
	return (node);
}


/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find built-ins: 
 * echo, cd, pwd, export, unset, env and exit
 * @return EXIT_FAILURE if no built-in was found
 * @todo 
 * 1) needs to be passed to actual process,
 * 2) exit(EXIT_FAILURE) is it really neccesary?
 * 3) MAYBE MAKE IT A BOOL?
*/
void	micro_check_for_meta(t_parser *node, t_env *env)
{
	if (ft_strnstr(node->sign, "$", ft_strlen(node->sign)) == 0)
		which_sign(node, env);
	if (ft_strnstr(node->sign, ">>", ft_strlen(node->sign)) || ft_strnstr(node->sign, "<<", ft_strlen(node->sign)) == 0)
		which_sign(node, env);
	if (ft_strnstr(node->sign, ">", ft_strlen(node->sign)) || ft_strnstr(node->sign, "<", ft_strlen(node->sign)) == 0)
		which_sign(node, env);
	if (ft_strnstr(node->sign, "|", ft_strlen(node->sign)) == 0)
		which_sign(node, env);
}

void	which_sign(t_parser *node, t_env *env)
{
	
}

t_expand *init_expand_list(void *content)
{
    t_expand *new;

    new = (t_expand *)malloc(sizeof(* new);
    if (!new)
        micro_error("malloc", errno);
    new->sign = NULL;
    new->str = NULL;
    new->builtin = NULL;
    new->next = NULL;
}