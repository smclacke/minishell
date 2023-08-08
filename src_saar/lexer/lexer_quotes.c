/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 17:07:01 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 16:50:14 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * @brief	splitting on spaces but when quote is found, create substring from first to last quote
 * @param	input from readline to tokenise
 * @param	c will be spaces, need to get rid of them all except for within quotes
 * @return	array of split up words with quotes handled separately including spaces within quotes
*/
char	**ft_split_shelly(char *input, char c)
{
	char	**array;

	if (!input)
		return (NULL);
	array = (char **)ft_calloc((ft_words(input, c)))
}
