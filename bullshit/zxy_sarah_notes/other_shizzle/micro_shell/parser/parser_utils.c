/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 16:37:55 by smclacke      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/09/01 14:37:44 by smclacke      ########   odam.nl         */
=======
/*   Updated: 2023/09/01 13:10:33 by smclacke      ########   odam.nl         */
>>>>>>> sarah
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	else if (ft_strcmp(tokens, "env") == 0) // add exit
		return (true);
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

