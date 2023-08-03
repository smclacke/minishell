/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 17:07:01 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/01 21:50:28 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

// ALL OF THESE FUNCTIONS NEED A LOT OF WORK
// FIGURE OUT WHAT i'M DOING IN THE LEXER AND LEAVE THE REST FOR THE PARSER....

/**
 * bleh, probably use this in parser instead of lexer, miss toch nodig, geen idee..
*/
// int	sign_tokens(char *input)
// {
// 	int		i = 0;
// 	while (input[i])
// 	{
// 		if (ft_strcmp(&input[i], "$") == 0)
// 			return (DOLLAR);
// 		else if (ft_strcmp(&input[i], ">>") == 0)
// 			return (MOREMORE);
// 		else if (ft_strcmp(&input[i], ">") == 0)
// 			return (MORE);
// 		else if (ft_strcmp(&input[i], "<<") == 0)
// 			return (LESSLESS);
// 		else if (ft_strcmp(&input[i], "<") == 0)
// 			return (LESS);
// 		else if (ft_strcmp(&input[i], "|") == 0)
// 			return (PIPE); 
// 		i++;
// 	}
// 	return (0);
// }

/**
 * THIS NEEDS TO CHANGE, LEXER OR PARSER USEFUL??
 * @brief	if quotation is encountered in the command line input, find the last quotation in the string
 * 			and return it to parse_input to add to the array of strings to be tokenized.
 * @param	input from the command line
 * @return	string with all quotations from the input to be put into the array and tokenized
*/
char	*quote_tokens(char *input)
{
	char	*quote_strs = NULL;
	int		i = 0;

	while (input[i])
	{
		if (input[i] == '\'' && closed_quotes(&input[i]))
			quote_strs = &input[i + closed_quotes(&input[i])];
		if (input[i] == '\"' && closed_quotes(&input[i]))
			quote_strs = &input[i + closed_quotes(&input[i])];
		i++;
	}
	return (quote_strs);
}

/**
 * THIS ALSO NEEDS TO CAHNGE, LEXER OR PARSER USEFUL??
 * @brief	if a single quotation is found, the string to searched to find the corresponding single qutation
 * 			same for double quotations
 * 			if the number of the type of quotations that are found is not even, the quotes can't be closed 
 * 			and therefore must error. 
 * @param	input from the command line
 * @return	will error if matching quotations are not closed, will return the index of closed quotations
*/
int	closed_quotes(char *input)
{
	int	i;
	int	count_double;
	int	count_single;

	i = 0;
	count_double = 0;
	count_single = 0;
	while (input[i])
	{
		if (ft_isdouble_q(input[i]))
			count_double++;
		i++;
	}
	i = 0;
	while (input[i])
	{
		if (ft_issingle_q(input[i]))
			count_single++;
		i++;
	}
	if ((count_double % 2) != 0 || (count_single % 2) != 0)
		return (0); // ERROR HERE ...  and quit (?)
	return (i);
}

/**
 * err.... am i going to use this?
 * find quotes, return substring from first quote to last quote in the input (not necessarily 
 * the pair of quotes, will handle this properly in parser)
 * if unclosed, throw error
*/
char	*check_quotes(char *input)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = ft_strlen(input);
	while (len > 0)
	{
		if (ft_isquote(input[len]))
		{
			ret = ft_substr(input, i, len + 1);
			if (!ret)
				return (0);
			return (ret);
		}
		--len;
	}
	return (0); // ERROR HERE ...  and quit (?)
}
