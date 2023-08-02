/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 16:37:55 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/02 15:35:18 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	parser_cmp_pipe(t_lexer *tokens)
{
	if (!tokens)
		return (false);
	if (ft_strnstr(tokens->input, "|", 1) == 0)
		return (true);
	return (false);
}

bool	parser_cmp_char_builtins(char *tokens)
{
	if (!tokens)
		return (false);
	if (ft_strcmp(tokens, "echo") == 0)
		return (true);
	else if (ft_strcmp(tokens, "cd") == 0)
		return (true);
	else if (ft_strcmp(tokens, "pwd") == 0)
		return (true);
	else if (ft_strcmp(tokens, "export") == 0)
		return (true);
	else if (ft_strcmp(tokens, "unset") == 0)
		return (true);
	else if (ft_strcmp(tokens, "env") == 0)
		return (true);
	return (false);
}

bool	parser_cmp_builtins(t_lexer *tokens)
{
	if (!tokens)
		return (false);
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
	if (!tokens)
		return (false);
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
// is this enough/going to work for all cases?
bool	parser_cmp_abso(t_lexer *tokens)
{
	if (!tokens)
		return (false);
	if (ft_strnstr(tokens->input, "/bin", ft_strlen(tokens->input)))
		return (true);
	else if (ft_strnstr(tokens->input, "/usr", ft_strlen(tokens->input)))
		return (true);
	return (false);
}
