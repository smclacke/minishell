/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/17 19:33:58 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// everything starts and finishes here.... let's goooooooo
		 // WE MUST SEPARATE METAS
	// split on spaces, split on metas but add metas to token array
	// if quotes, split those apart keep them totally intact

static int	len_token(char *input)
{
	int	i = 0;

	if (is_token(&input[i]) == 2)
	{
		printf("&input: %s\n", &input[i]);
		printf("is meta: %i\n", is_token(&input[i]));
		i++;
		return (is_token(&input[i]));
	}
	else if (is_token(&input[i]) == 1)
		return (is_token(&input[i]));
	while (input[i] && !ft_isspace(input[i])
			&& !is_token(&input[i]))
	{
		if (ft_isquote(input[i]))
		{
			i++;
			i += next_quote(&input[i], input[i]);
			// printf("LT | index = %i\n", i);
			return (i);
		}
		printf("this is fucked\n");
		i++;
	}
	return (i);
}

static char	*give_tokens(char *input)
{
	char	*token;
	int		token_len;

	token_len = len_token(input);
	token = ft_substr(input, 0, token_len);
	if (!token)
		return (NULL);
	input += token_len;
	return (token);
}

static int	amount_tokens(char *input)
{
	int	i = 0;
	int	count = 0;

	// printf("AT | INPUT = %s\n", input);
	while (input[i])
	{
		i += len_token(&input[i]);
		count++;
		// printf("AT | count = %i\n", count);
	}
	return (count);
}

static bool	annoying_split(char *input)
{
	int	i = 0;
	
	while (input[i])
	{
		if (ft_isquote(input[i]) || is_meta(&input[i]))
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief	takes the input string from the command line, iterates through it. While there
 * 			are no quotations, the string is split on spaces with metas (exc. dollar) also being 
 * 			split into separate str. If a quotation is encountered, the matching quote is found and
 * 			all of that input is put into token
 * @param	input input from the command line
 * @return	2D array of separated strings made from the input, ready to be tokenized
*/
char	**parse_input(char *input)
{
	char	**array = NULL;
	int		no_tokens = 0;
	int		i = 0;

	if (annoying_split(input))
	{
		printf("input: %s\n", input);
		no_tokens = amount_tokens(input);
		printf("amount of toks: %i", no_tokens);
		array = (char **)malloc(sizeof(char *) * no_tokens + 1);
		while (i < no_tokens)
		{
			// printf("i = %i | no_tokens = %i\n", i, no_tokens);
			// array[i] = give_tokens(input);
			printf("PI | array =  %s\n", array[i]);
			i++;
		}
	}
	else
		array = ft_split(input, ' ');;
	if (!array)
		return (NULL);
	return (array);
}
