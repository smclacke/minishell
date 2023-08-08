/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 01:14:02 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 21:34:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * @brief	Check if there are any quotes, doesn't matter if they're closed
 * 			will be removed to check if string is a cmd or not
 * @param	tokens take the token->input (char *) to check through the string
 * @return	bool: true/false 1/0
*/
// bool	parser_check_quotes(char *tokens)
// {
// 	char	*tmp;
// 	int		i = 0;
	
// 	tmp = tokens;
// 	while (tmp[i])
// 	{
// 		if (ft_isquote(tmp[i]))
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

// /**
//  * @brief	count the amount of quotes within the string
//  * @param	tokens takes the token as a char * to iterate through the string
//  * @return	amount of quotes found, can then remove them from index count for the string
//  * 			without quotes which will be passed back to function which checks whether
//  * 			it's a valid cmd or not regardless of the quotations
// */
// static int		count_quotes(char *tokens)
// {
// 	char	*tmp;
// 	int		found = 0;
// 	int		i = 0;

// 	tmp = tokens;
// 	while (tmp[i])
// 	{	
// 		if (ft_isquote(tmp[i]))
// 			found++;
// 		i++;
// 	}
// 	return (found);
// }

// /**
//  * @brief	if there are quotations, remove them and put temp string into variable to check if 
//  * 			it's a valid cmd, if not, take the original string token as input
//  * @param	tokens takes the token as a char * to iterate through the string 
//  * @return	string without the quotation to check if it is a valid cmd regardless of the quotations
// */
// char	*remove_quotes(char *tokens)
// {
// 	char	*removed;
// 	int		quote_amount;
// 	int		without;
// 	int		i = 0;
// 	int		j = 0;

// 	quote_amount = count_quotes(tokens);
// 	without = (ft_strlen(tokens) - quote_amount);
// 	removed = malloc(sizeof(char) * (without + 1));
// 	if (!removed)
// 		return (0);
// 	while (tokens[i])
// 	{
// 		if (tokens[i] && !ft_isquote(tokens[i]))
// 		{	
// 			removed[j] = tokens[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	removed[j] = '\0';
// 	return (removed);
// }

/**
//  * @brief	if quotation is encountered in the command line input, find the last quotation in the string
//  * 			and return it to parse_input to add to the array of strings to be tokenized.
//  * @param	input from the command line
//  * @return	string with all quotations from the input to be put into the array and tokenized
// */
// char	*quote_tokens(char *input)
// {
// 	char	*quote_strs = NULL;
// 	int		i = 0;

// 	while (input[i])
// 	{
// 		if (input[i] == '\'' && closed_quotes(&input[i]))
// 			quote_strs = &input[i + closed_quotes(&input[i])];
// 		if (input[i] == '\"' && closed_quotes(&input[i]))
// 			quote_strs = &input[i + closed_quotes(&input[i])];
// 		i++;
// 	}
// 	return (quote_strs);
// }

// // /**
// //  * @brief	if a single quotation is found, the string to searched to find the corresponding single qutation
// //  * 			same for double quotations
// //  * 			if the number of the type of quotations that are found is not even, the quotes can't be closed 
// //  * 			and therefore must error. 
// //  * @param	input from the command line
// //  * @return	will error if matching quotations are not closed, will return the index of closed quotations
// // */
// int	closed_quotes(char *input)
// {
// 	int	i;
// 	int	count_double;
// 	int	count_single;

// 	i = 0;
// 	count_double = 0;
// 	count_single = 0;
// 	while (input[i])
// 	{
// 		if (ft_isdouble_q(input[i]))
// 			count_double++;
// 		i++;
// 	}
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (ft_issingle_q(input[i]))
// 			count_single++;
// 		i++;
// 	}
// 	if ((count_double % 2) != 0 || (count_single % 2) != 0)
// 		return (0); // ERROR HERE ...  and quit (?)
// 	return (i);
// }

// // /**
// //  * err.... am i going to use this?
// //  * find quotes, return substring from first quote to last quote in the input (not necessarily 
// //  * the pair of quotes, will handle this properly in parser)
// //  * if unclosed, throw error
// // */
// char	*check_quotes(char *input)
// {
// 	int		i;
// 	int		len;
// 	char	*ret;

// 	i = 0;
// 	len = ft_strlen(input);
// 	while (len > 0)
// 	{
// 		if (ft_isquote(input[len]))
// 		{
// 			ret = ft_substr(input, i, len + 1);
// 			if (!ret)
// 				return (0);
// 			return (ret);
// 		}
// 		--len;
// 	}
// 	return (0); // ERROR HERE ...  and quit (?)
// }

