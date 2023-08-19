/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 17:07:01 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/19 14:20:01 by SarahLouise   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"


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

static char	*make_quotes(char *input)
{
	int		i = 0;
	int		len;
	char	*quotes;

	len = quote_len(input);
	quotes = (char *)malloc(sizeof(char) * (len + 1));
	if (!quotes)
		return (0);
	while (i < len)
	{
		quotes[i] = input[i];
		i++;
	}
	quotes[i] = '\0';
	return (quotes);
}

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
			if (lq_isquote(*input))
				array[i] = make_quotes(&input);
			else
				array[i] = make_words(&input);
		}
		i++;
		while (*input && !lq_what_to_split(*input))
			input++;
	}
	array[i] = NULL;
	return (array);
}
