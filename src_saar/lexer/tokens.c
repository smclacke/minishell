/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 17:45:04 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/10 14:12:00 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

// parse space
void	parse_space(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
}

// check if there are any quotes
// char	*find_quotes(char *input)
// {
// 	// if ive found a quote, 
// 	if (!second_quote(input, ft_isquote(intput[i]))) // isquote returns either single or double which can be passed into second_quote()
// 		return (0);
// 	else 
// 		// split quoted part from rest
// 		// return specific part of input with quotes attached
// }
// // find next quotation
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

// // need to be separate tokens, > < >> <<
// char	*find_redirect(char *input)
// {

// }

// // need to be separate tokens, ; | &
// char	*find_delimiter(char *input)
// {
	
// }
