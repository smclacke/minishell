/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 16:37:55 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/26 18:40:29 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * compare the first token to cmds and valid signs, else throw error
*/
bool	micro_cmp_builtins(t_lexer *tokens)
{
	int	i = 0;

	if (ft_strcmp((char *)&tokens[i], "echo") == 0)
		return (true);
	else if (ft_strcmp((char *)&tokens[i], "cd") == 0)
		return (true);
	else if (ft_strcmp((char *)&tokens[i], "pwd") == 0)
		return (true);
	else if (ft_strcmp((char *)&tokens[i], "export") == 0)
		return (true);
	else if (ft_strcmp((char *)&tokens[i], "unset") == 0)
		return (true);
	else if (ft_strcmp((char *)&tokens[i], "env") == 0)
		return (true);
	return (false);
}

bool	micro_cmp_signs(t_lexer *tokens)
{
	int	i = 0;

	if (ft_strcmp((char *)&tokens[i], ">>") == 0 || ft_strcmp((char *)&tokens[i], "<<") == 0)
			return (true);
	else if (ft_strcmp((char *)&tokens[i], ">") == 0 || ft_strcmp((char *)&tokens[i], "<") == 0)
		return (true);
	else if (ft_strcmp((char *)&tokens[i], "$") == 0)
		return (true);
	return (false);
}

/**
 * get first token, valid or not? bool
 * if not, we can immediately error and not check the rest
 * !! GOT TO HANDLE WHEN THERE ARE QUOTES IN CMDS, SINGLE AND DOUBLE
*/
bool	micro_first_token(t_lexer *tokens)
{
	int	i = 0;

	if (micro_cmp_signs(&tokens[i]))
		return (true);
	else if (micro_cmp_builtins(&tokens[i]))
		return (true);
	return (false);
}
