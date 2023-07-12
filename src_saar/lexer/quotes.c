/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 17:07:01 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/12 17:27:34 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * RIGHT NOW: does not tokenize if not closed based on spaces
 * check if all quotes are closed or not
 * if this fails, throw an ERRROROROROR
 * NEED TO CHECK WHICH QUOTES AND IF THEY MATCH
 * right now, 1x double and 1x single still tokenizes. 
*/
int	closed_quotes(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (ft_isquote(input[i]))
			count++;
		i++;
	}
	if ((count % 2))
		return (0);
	return (1);
}


/**
 * find quotes
 * check for dollar in double quotes!!
 * if unclosed, throw error
*/
// char	*find_quote(char *input)
// {
// 	// if ive found a quote, 
// 	if (!second_quote(input, ft_isquote(intput[i]))) // isquote returns either single or double which can be passed into second_quote()
// 		return (0);
// 	else 
// 		// split quoted part from rest
// 		// return specific part of input with quotes attached
// }
