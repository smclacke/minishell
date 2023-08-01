/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 01:14:02 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/01 16:42:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

bool	parser_check_quotes(t_lexer *tokens)
{
	char	*tmp;
	int		i = 0;
	
	tmp = (char *)tokens->input;
	while (tmp[i])
	{
		if (ft_isquote(tmp[i]))
			return (true);
		i++;
	}
	return (false);
}

static int		count_quotes(t_lexer *tokens)
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

char	*remove_quotes(t_lexer *tokens) // double quotes failing???
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
