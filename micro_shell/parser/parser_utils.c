/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 16:37:55 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/26 16:39:09 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * compare the first token to cmds and valid signs, else throw error
*/
bool	micro_cmp_builtins(t_lexer *tokens)
{
	if (ft_strcmp(tokens, "echo") == 0)
		return (true);
	if (ft_strcmp(tokens, "cd") == 0)
		return (true);
	if (ft_strcmp(tokens, "pwd") == 0)
		return (true);
	if (ft_strcmp(tokens, "export") == 0)
		return (true);
	if (ft_strcmp(tokens, "unset") == 0)
		return (true);
	if (ft_strcmp(tokens, "env") == 0)
		return (true);
	return (false);
}

bool	micro_cmp_signs(t_lexer *tokens)
{
	if (ft_strcmp(tokens, ">>") == 0 || ft_strcmp(tokens, "<<") == 0)
			return (true);
	if (ft_strcmp(tokens, ">") == 0 || ft_strcmp(tokens, "<") == 0)
		return (true);
	if (ft_strcmp(tokens, "$") == 0)
		return (true);
	return (false);
}

/**
 * get first token, valid or not? bool
 * if not, we can immediately error and not check the rest
*/
bool	micro_first_token(t_lexer *tokens)
{
	if (micro_cmp_signs(tokens))
		return (true);
	if (micro_cmp_builtins(tokens))
		return (true);
	return (false);
}
