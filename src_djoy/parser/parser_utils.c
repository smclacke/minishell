/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 18:03:01 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * need to wrtie this function
*/
bool	parser_cmp_squote(t_parser *tokens)
{
	if (!tokens)
		return (false);
	return (false);
}
/**
 * need to wrtie this function
*/
bool	parser_cmp_dquote(t_parser *tokens)
{
	if (!tokens)
		return (false);
	return (false);
}

bool	parser_cmp_builtins(t_parser *tokens)
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

bool	parser_cmp_metas(t_parser *tokens)
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
	else if ((ft_strnstr(tokens->input, "|", 1)))
		return (true);
	return (false);
}

bool	parser_cmp_abso(t_parser *tokens)
{
	if (!tokens)
		return (false);
	if (ft_strnstr(tokens->input, "/", ft_strlen(tokens->input)))
		return (true);
	else if (ft_strnstr(tokens->input, "./", ft_strlen(tokens->input)))
		return (true);
	else if (ft_strnstr(tokens->input, "../", ft_strlen(tokens->input)))
		return (true);
	return (false);
}