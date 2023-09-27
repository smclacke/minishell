/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_size.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:03:30 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/27 19:07:37 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	find the start position of each token
 * 			old_start from previous position is added inc. spaces
 * 			if meta is encountered, immediately return that position
 * 			(metas become their own tokens separately)
 * 			if quote, find matching quote and keep iterating
 * 			until the next space (outside the quotes) is found
 * @param	input from command line
 * @param	old_start from previous token
 * @return	new_start = new starting position of token needed to be made
*/
int	start_token(char *input, int old_start)
{
	int 	new_start;
	char	*quote_type;

	new_start = 0;
	quote_type = NULL;
	while (input[old_start] && ft_isspace(input[old_start]))
		old_start++;
	new_start = old_start;
	while (input[old_start] && !ft_isspace(input[old_start]))
	{
		if (ft_ismeta(input[old_start]))
			return (new_start);
		if (ft_isquote(input[old_start]))
		{
			quote_type = which_quote(&input[old_start]);
			old_start += next_quote(&input[old_start], *quote_type);
		}
		old_start++;
	}
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
	int		j;
	char	*quote_type;

	j = 0;
	quote_type = NULL;
	while (input[len] && ft_isspace(input[len]))
		len++;
	j = len;
	if (ft_ismeta(input[len]))
	{
		len += is_meta(&input[len]);
		len = len - j;
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
	len = len - j;
	return (len);	
}

/**
 * @brief	
 * @param	
 * @param	
 * @return	
*/
int	amount_tokens(char *input)
{
	int		i;
	int		count;
	char	*quote_type;

	i = 0;
	count = 0;
	quote_type = NULL;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (ft_ismeta(input[i]))
		{
			if (ft_ismeta(input[i + 1])) // like... different?
				i++;
			count++;
			i++;
		}
		if (input[i] && !ft_isspace(input[i]))
		{
			while (input[i] && !space_or_meta(input[i]))
			{
				if (ft_isquote(input[i]))
				{
					quote_type = which_quote(&input[i]); //
					i += next_quote(&input[i], *quote_type); // these two in one func ?
				}
				i++;
			}
			count++;
		}
	}
	return (count);
}
