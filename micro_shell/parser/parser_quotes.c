/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 01:14:02 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/03 14:39:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief	Check if there are any quotes, doesn't matter if they're closed
 * 			will be removed to check if string is a cmd or not
 * @param	tokens take the token->input (char *) to check through the string
 * @return	bool: true/false 1/0
*/
bool	parser_check_quotes(char *tokens)
{
	char	*tmp;
	int		i = 0;
	
	tmp = tokens;
	while (tmp[i])
	{
		if (ft_isquote(tmp[i]))
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief	count the amount of quotes within the string
 * @param	tokens takes the token as a char * to iterate through the string
 * @return	amount of quotes found, can then remove them from index count for the string
 * 			without quotes which will be passed back to function which checks whether
 * 			it's a valid cmd or not regardless of the quotations
*/
static int		count_quotes(char *tokens)
{
	char	*tmp;
	int		found = 0;
	int		i = 0;

	tmp = tokens;
	while (tmp[i])
	{	
		if (ft_isquote(tmp[i]))
			found++;
		i++;
	}
	return (found);
}

/**
 * @brief	if there are quotations, remove them and put temp string into variable to check if 
 * 			it's a valid cmd, if not, take the original string token as input
 * @param	tokens takes the token as a char * to iterate through the string 
 * @return	string without the quotation to check if it is a valid cmd regardless of the quotations
*/
char	*remove_quotes(char *tokens)
{
	char	*removed;
	int		quote_amount;
	int		without;
	int		i = 0;
	int		j = 0;

	quote_amount = count_quotes(tokens);
	without = (ft_strlen(tokens) - quote_amount);
	removed = malloc(sizeof(char) * (without + 1));
	if (!removed)
		return (0);
	while (tokens[i])
	{
		if (tokens[i] && !ft_isquote(tokens[i]))
		{	
			removed[j] = tokens[i];
			j++;
		}
		i++;
	}
	removed[j] = '\0';
	return (removed);
}
