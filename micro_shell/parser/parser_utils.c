/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 16:37:55 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/31 16:32:28 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
bool	micro_cmp_builtins(t_lexer *tokens)
{
	t_lexer		*tmp;

	tmp = tokens;
	if (ft_strcmp(tokens->input, "echo") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, "cd") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, "pwd") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, "export") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, "unset") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, "env") == 0)
		return (true);
	return (false);
}

bool	micro_cmp_signs(t_lexer *tokens)
{
	if ((ft_strcmp(tokens->input, ">>") == 0) || (ft_strcmp(tokens->input, "<<") == 0))
		return (true);
	else if ((ft_strcmp(tokens->input, ">") == 0) || (ft_strcmp(tokens->input, "<") == 0))
		return (true);
	else if ((ft_strcmp(tokens->input, "$") == 0))
		return (true);
	return (false);
}

/**
 * compare the first token to cmds and valid signs, else throw error
*/
bool	micro_first_token(t_lexer *tokens, t_parser *parser_struct)
{
	int	i = 0;

	if (micro_cmp_signs(&tokens[i]))
	{
		parser_struct->sign = tokens->input;
		printf("sign: %s\n", parser_struct->sign);
		return (true);
	}
	else if (micro_cmp_builtins(&tokens[i]))
	{	
		parser_struct->cmd = tokens->input;
		printf("cmd: %s\n", parser_struct->cmd);
		return (true);
	}
	return (false);
}
