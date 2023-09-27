/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/27 17:10:51 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	
 * @param	
 * @param	
 * @return	
*/
static int	amount_tokens(char *input)
{
	int		i = 0;
	int		count = 0;
	char	*quote_type = NULL;

	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (ft_ismeta(input[i]))
		{
			if (ft_ismeta(input[i + 1])) // like... different?
				i++;
			count++;
			i++;
		}
		if (input[i] && !ft_isspace(input[i]))
		{
			while (input[i] && !ft_isspace(input[i]) && !ft_ismeta(input[i]))
			{
				if (ft_isquote(input[i]))
				{
					quote_type = which_quote(&input[i]); //
					i += next_quote(&input[i], *quote_type); // these two in one func ?
				}
				i++;
			}
			count++;
		}
	}
	return (count);
}

/**
 * @brief	
 * @param	
 * @param	
 * @return	
*/
static char	*split_tokens(char *input, int len)
{
	char	*token;

	token = ft_substr(input, 0, len);
	if (!token)
		return (NULL);
	input += len;
	return (token);
}

/**
 * @brief	if there's quotation and/or meta char, need to find them and
 * 			split them accordingly. Otherwise, just split on spaces
 * @param	input input from the command line
 * @return	1 yes there's a meta and/or quotation. 0 false
*/
static int	parser_split(char *input)
{
	int	i = 0;

	while (input[i])
	{
		if (ft_isquote(input[i]) || ft_ismeta(input[i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief	takes the input string from the command line, 
 * 			iterates through it. If there are quoations and/or meta chars,
 * 			input is split on metas, quotations and spaces.
 * 			otherwise only spaces
 * @param	input input from the command line
 * @return	2D array of separated strings made from the input, 
 * 			ready to be tokenized into the parser struct list of tokens
*/
char	**parse_input(char *input)
{
	char	**array = NULL;
	int		no_tokens = 0;
	int		start = 0;
	int		len = 0;
	int		i = 0;

	if (parser_split(input))
	{
		no_tokens = amount_tokens(input);
		printf("no_tokens: %i\n", no_tokens);
		array = (char **)malloc(sizeof(char *) * (no_tokens + 1));
		if (!array)
			return (NULL);
		while (i < no_tokens)
		{
			start = start_token(input, (start + len));
			printf("start = %i\n", start);
			len = len_token(input, start);
			array[i] = (char *)malloc(sizeof(char) * (len + 1));
			array[i] = split_tokens(&input[start], len);
			i++;
		}
		array[no_tokens] = NULL;
	}
	else
		array = ft_split(input, ' ');
	if (!array)
		return (NULL);   /// does this protect the while loop array?
					/// ++ maybe the if statment one...?
	return (array);
}
