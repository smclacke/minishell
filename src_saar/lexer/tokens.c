/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 17:45:04 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/11 20:57:27 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

// parse space
void	parse_space(char *input)
{
	while (ft_isspace(*input))
		input++;
}

/*
 *	check if there are any quotes
 *	IF DOLLAR IN DOUBLE QUOTE, STILL HANDLE AS META DOLLAR
 *	if unclosed quotes, throw error
*/
// char	*find_quotes(char *input)
// {
// 	// if ive found a quote, 
// 	if (!second_quote(input, ft_isquote(intput[i]))) // isquote returns either single or double which can be passed into second_quote()
// 		return (0);
// 	else 
// 		// split quoted part from rest
// 		// return specific part of input with quotes attached
// }

/**
 *	find next quotation
 *	if unclosed, throw error
*/
// int	second_quote(char *input, char c)
// {
// 	int	i;

// 	i = 1;
// 	while (input[i] != c && input[i])
// 		i++;
// 	if (!input[i])
// 		return (0);
// 	return (i);
// }

/*
 *	redirect = << >>, < >, and pipe
*/
// char	*find_redirect(char *input)
// {

// }

/**
 * = whatever is after <<, for HERE_DOC
*/
// char	*find_delimiter(char *input)
// {
	
// }

/*
 *	find builtins 
 *∫	
*/

