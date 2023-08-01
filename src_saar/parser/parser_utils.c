/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/01 17:41:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

bool	parser_cmp_pipe(t_lexer *tokens)
{
	if (ft_strnstr(tokens->input, "|", 1) == 0)
		return (true);
	return (false);
}

bool	parser_cmp_builtins(t_lexer *tokens)
{
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

bool	parser_cmp_signs(t_lexer *tokens)
{
	if (ft_strnstr(tokens->input, ">>", 2))
		return (true);
	else if (ft_strnstr(tokens->input, "<<", 2))
		return (true);
	else if ((ft_strnstr(tokens->input, ">", 1)))
		return (true);
	else if (ft_strnstr(tokens->input, "<", 1))
		return (true);
	else if ((ft_strnstr(tokens->input, "$", 1)))
		return (true);
	return (false);
}

bool	parser_cmp_abso(t_lexer *tokens)
{
	if (ft_strnstr(tokens->input, "/bin", ft_strlen(tokens->input)))
		return (true);
	else if (ft_strnstr(tokens->input, "/usr", ft_strlen(tokens->input)))
		return (true);
	return (false);
}

bool	parser_cmp(t_lexer *tokens, t_lexer *parser_struct)
{
	if (parser_cmp_abso(tokens))
		return (true);
	else if (parser_cmp_signs(tokens))
		return (true);
	else if (parser_cmp_builtins(tokens))
		return (true);
	else if (parser_cmp_pipe(tokens))
		return (true);
	return (false);
}
