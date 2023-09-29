/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_size.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:03:30 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/28 23:10:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	find the start position of each token
 * 			old_start from previous position is added inc. spaces
 * @param	input from command line
 * @param	old_start from previous token
 * @return	new_start = new starting position of next token to make
*/
int	start_token(char *input, int old_start)
{
	int		new_start;
	char	*quote_type;

	new_start = 0;
	quote_type = NULL;
	while (input[old_start] && ft_isspace(input[old_start]))
		old_start++;
	new_start = old_start;
	return (new_start);
}

/**
 * @brief	getting the length of the token i want to make
 * 			add the starting position of the previous
 * 			token (len), remove old starting position inc. spaces = j
 * 			from new length (len = len - j) (len is now current pos)
 * 			if meta, len = 1 or 2 
 * 			if quote, find matching quote and keep iterating
 * 			until the next space (outside the quotes) is found
 * @param	input from command line
 * @param	len previous tokens starting position
 * @return	len = new length of current token needing to be made
*/
int	len_token(char *input, int len)
{
	int		tmp;
	char	*quote_type;

	tmp = 0;
	quote_type = NULL;
	while (input[len] && ft_isspace(input[len]))
		len++;
	tmp = len;
	if (ft_ismeta(input[len]))
	{
		len += is_meta(&input[len]);
		len = len - tmp;
		return (len);
	}
	while (input[len] && !space_or_meta(input[len]))
	{
		if (ft_isquote(input[len]))
		{
			quote_type = which_quote(&input[len]);
			len += next_quote(&input[len], *quote_type);
		}
		len++;
	}
	len = len - tmp;
	return (len);
}

/**
 * @brief	gets the index position after parsing through the
 * 			input of characters as long as there are no metas
 * 			or spaces, handling quotations, for amount_tokens()
 * @param	input from the command line
 * @param	i current index of input
 * @return	index after parsing through chars and quotes
*/
static int	quote_input(char *input, int i)
{
	char	*quote_type;

	quote_type = (char *)malloc(sizeof(char) * 2);
	if (!quote_type)
		exit(EXIT_FAILURE);
	while (input[i] && !space_or_meta(input[i]))
	{
		if (ft_isquote(input[i]))
		{
			quote_type = which_quote(&input[i]);
			i += next_quote(&input[i], *quote_type);
		}
		i++;
	}
	return (i);
}

/**
 * @brief	parses through the input and counts how many "words"
 * 			quoted strings and metas, returns the amount so that
 * 			array can be given enough space to store these tokens in
 * @param	input from the command line
 * @return	count amount of strings that will be put into array 
 * 			and then tokenized
*/
int	amount_tokens(char *input)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (ft_ismeta(input[i]))
		{
			if (ft_ismeta(input[i + 1]))
				i++;
			count++;
			i++;
		}
		if (input[i] && !ft_isspace(input[i]))
		{
			i = quote_input(input, i);
			count++;
		}
	}
	return (count);
}
