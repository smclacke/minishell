/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/01 00:47:21 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

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
	if ((ft_strcmp(tokens->input, ">>") == 0) || (ft_strcmp(tokens->input, "<<") == 0))
		return (true);
	else if ((ft_strcmp(tokens->input, ">") == 0) || (ft_strcmp(tokens->input, "<") == 0))
		return (true);
	else if ((ft_strcmp(tokens->input, "$") == 0))
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

bool	parser_check_quotes(t_lexer *tokens)
{
	if (ft_strnstr(tokens->input, "\'", ft_strlen(tokens->input)))
		return (true);
	else if (ft_strnstr(tokens->input, "\'", ft_strlen(tokens->input)))
		return (true);
	return (false);
}

int		count_quotes(t_lexer *tokens)
{
	char	*tmp;
	int		found = 0;
	int		i = 0;

	tmp = (char *)tokens->input;
	while (tmp[i])
	{	
		if (ft_isquote(tmp[i]))
			found++;
		i++;
	}
	return (found);
}

char	*remove_quotes(t_lexer *tokens)
{
	char	*tmp;
	char	*removed;
	int		quote_amount;
	int		without;
	int		i = 0;
	int		j = 0;

	quote_amount = count_quotes(tokens);
	tmp = (char *)tokens->input;
	without = (ft_strlen(tmp) - quote_amount);
	removed = malloc(sizeof(char) * (without + 1));
	if (!removed)
		return (0);
	while (tmp[i])
	{
		if (tmp[i] && !ft_isquote(tmp[i]))
		{	
			removed[j] = tmp[i];
			j++;
		}
		i++;
	}
	removed[j] = '\0';
	return (removed);
}
