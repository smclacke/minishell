/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_size.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:03:30 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/31 19:43:55 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo errors??????????
*/

/**
 * @brief	find the start position of each token
 * 			old_start from previous position is added inc. spaces
 * @param	input from command line
 * @param	old_start from previous token
 * @return	new_start = new starting position of next token to make
*/
int	start_token(char *input, int old_start)
{
	while (input[old_start] && ft_isspace(input[old_start]))
		old_start++;
	return (old_start);
}

/**
 * @brief	gets the length of the token i want to make
 * 			add the starting position of the previous
 * 			token (len), remove old starting position inc. spaces
 * 			from new length (len = len - tmp) (len is now current pos)
 * 			if quote, find matching quote and keep iterating
 * 			until the next space (outside the quotes) is found
 * @param	input from command line
 * @param	len previous token's starting position
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
