/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_bullshit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 17:07:01 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/04 21:13:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"


/**
 * @brief	length of string without the quotes that are going to be removed
 * 			encounter a quote, find matching, remove both, keep everything
 * 			inside those quotes intact
*/
int	len_quotes(char *str)
{
	int	i;
	int	q;
	int	len;

	i = 0;
	q = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] && !ft_isquote(str[i]))
			increment(&len, &i);
		if (ft_isquote(str[i]))
		{
			q = quote_type(str[i]);
			i++;
			while (str[i] && str[i] != q)
				increment(&len, &i);
		}
		if (ft_isquote(str[i]) && str[i] == q)
			i++;
	}
	return (len);
}

/**
 * @brief	if a single quotation is found, the string to searched to find the corresponding single qutation
 * 			same for double quotations
 * 			if the number of the type of quotations that are found is not even, the quotes can't be closed 
 * 			and therefore must error. 
 * @param	input from the command line
 * @return	will error if matching quotations are not closed, will return the index of closed quotations
*/
bool	closed_quotes(char *input)
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
		return (false);
	return (true);
}

/**
 * @brief	Check if there are any quotes and if they are closed
 * @param	tokens take the token->input (char *) to check through the string
 * @return	bool: true/false 1/0
*/
bool	shelly_check_quotes(char *tokens)
{
	char	*tmp;
	int		i = 0;
	
	tmp = tokens;
	while (tmp[i])
	{
		if (ft_isquote(tmp[i]))
		{	
			if (closed_quotes(tmp))
				return (true);
			else
				exit(EXIT_FAILURE); // need to error correctly for open quotes
		}
		i++;
	}
	return (false);
}


static char	*make_words(char *input)
{
	int		i = 0;
	int		len;
	char	*words;

	len = lq_word_length(input);
	words = (char *)malloc(sizeof(char) * (len + 1));
	if (!words)
		return (0);
	while (i < len)
	{
		words[i] = input[i];
		i++;
	}
	words[i] = '\0';
	return (words);
}

// char *make_quoted_string(char **input) {
//     char *start = *input;
//     char *end;

//     (*input)++; // Move past the opening quote

//     // Find the closing quote or the end of the string
//     while (**input != '\0' && **input != lq_isquote(start[0])) {
//         (*input)++;
//     }

//     end = *input;
//     if (**input != '\0') {
//         (*input)++; // Move past the closing quote
//     }

//     // Calculate the length of the substring
//     int length = end - start;

//     // Allocate memory for the substring
//     char *substring = (char *)malloc(length + 1);

//     if (substring != NULL) {
//         // Copy the substring into the allocated memory
//         for (int i = 0; i < length; i++) {
//             substring[i] = start[i];
//         }
//         substring[length] = '\0'; // Null-terminate the substring
//     }

//     return substring;
// }

// static char	*make_quotes(char *input)
// {
// 	int		i = 0;
// 	int		len;
// 	char	*quotes;

// 	len = quote_len(input);
// 	quotes = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!quotes)
// 		return (0);
// 	while (i < len)
// 	{
// 		quotes[i] = input[i];
// 		i++;
// 	}
// 	quotes[i] = '\0';
// 	return (quotes);
// }

char	**ft_split_shelly(char *input)
{
	char	**array;
	int		i = 0;

	array = (char **)malloc(sizeof(char *) * (lq_count_words(input) + 1));
	if (!array)
		return (0);
	while (*input)
	{
		while (*input && lq_what_to_split(*input))
			input++;
		if (*input)
		{
			// if (lq_isquote(*input))
			// 	array[i] = make_quotes(input);
			// else
			array[i] = make_words(input);
		}
		i++;
		while (*input && !lq_what_to_split(*input))
			input++;
	}
	array[i] = NULL;
	return (array);
}

//////////////////////////////////// some other shit

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


