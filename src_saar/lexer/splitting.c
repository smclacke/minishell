/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/13 20:40:27 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// everything starts and finishes here.... let's goooooooo
		 // WE MUST SEPARATE METAS
	// split on spaces, split on metas but add metas to token array
	// if quotes, split those apart keep them totally intact

static int	is_token(char *input)
{
	if (*input == '|')
		return (1);
	if (*input == '<')
	{
		if (!ft_strncmp(input, "<<", 2))
			return (1);
		return (2);
	}
	else if (*input == '>')
	{
		if (!ft_strncmp(input, ">>", 2))
			return (1);
		return (2);
	}
	return (0);
}

static int	len_token(char *input)
{
	int	i = 0;

	if (is_token(&input[i]))
		return (is_token(&input[i]));
	while (input[i] && !ft_isspace(input[i])
			&& !is_token(&input[i]))
	{
		if (ft_isquote(input[i]))
		{
			i += next_quote(&input[i], input[i]);
			return (i);
		}
		i++;
	}
	printf("index = %i\n", i);
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
	printf("give_token: %s\n", token);
	input += token_len;
	return (token);
}

static int	amount_tokens(char *input)
{
	int	i = 0;
	int	count = 0;

	while (input[i])
	{
		count += len_token(&input[i]);
		i++;
	}
	printf("count = %i\n", count);
	return (count);
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
	int		i = 0;

	while (input[i])
	{
		if (ft_isquote(input[i]) || is_meta(&input[i]))
		{
			i = 0;
			array = (char **)malloc(sizeof(char *) * amount_tokens(input));
			while (input)
			{
				array[i] = give_tokens(input);
				printf("parse_input_array: %s\n", array[i]);
				i++;
			}
			if (!array)
				return (NULL);
			return (array);
		}
		i++;
	}
	array = ft_split(input, ' ');
	if (!array)
		return (NULL);
	return (array);
}

	// printf("whats up?\n");