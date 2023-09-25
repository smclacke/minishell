/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/25 13:31:12 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// everything starts and finishes here.... let's goooooooo
		 // WE MUST SEPARATE METAS
	// split on spaces, split on metas but add metas to token array
	// if quotes, split those apart keep them totally intact
	// inc. something"thing"more = one token
	// ignore dollas

static int	len_token(char *input, int len)
{
	int	j = 0;
	while (input[len] && ft_isspace(input[len]))
		len++;
	j = len;
	while (input[len] && !ft_isspace(input[len]))
		len++;
	len = len - j;
	return (len);	
}

static int	start_token(char *input, int old_start)
{
	int j = 0;

	while (input[old_start] && ft_isspace(input[old_start]))
		old_start++;
	j = old_start;
	while (input[old_start] && !ft_isspace(input[old_start]))
		old_start++;
	return (j);	
}

static char	*split_tokens(char *input, int len)
{
	char	*token;

	token = ft_substr(input, 0, len);
	if (!token)
		return (NULL);
	input += len;
	return (token);
}

static int	amount_tokens(char *input)
{
	int		i = 0;
	int		count = 0;
	char	*quote_type = NULL;

	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (ft_isquote(input[i]))
		{
			quote_type = which_quote(&input[i]);
			i += next_quote(&input[i], *quote_type);
			printf("i = %i\n", i);
		}	
		count++;
		while (input[i] && !ft_isspace(input[i]))
			i++;
	}
	return (count);
}

// static int	amount_tokens(char *input)
// {
// 	int	i = 0;
// 	int	count = 0;
// 	while (input[i] && !ft_isquote(input[i]))
// 	{
// 		while (input[i] && ft_isspace(input[i]) && !ft_isquote(input[i]))
// 			i++;
// 		count++;
// 		while (input[i] && !ft_isspace(input[i]) && !ft_isquote(input[i]))
// 			i++;
// 	}
// 	if (ft_isquote(input[i]))
// 	{
// 		printf("is it here?\n");
// 		i += next_quote(input, *which_quote(input));
// 		count++;
// 	}
// 	return (count);
// }

static int	annoying_split(char *input)
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
	int		start = 0;
	int		len = 0;
	int		i = 0;

	if (annoying_split(input))
	{
		no_tokens = amount_tokens(input);
		printf("no_tokens: %i\n", no_tokens);
		array = (char **)malloc(sizeof(char *) * (no_tokens + 1));
		if (!array)
			return (NULL);
		while (i < no_tokens)
		{
			start = start_token(input, (start + len));
			len = len_token(input, start);
			array[i] = (char *)malloc(sizeof(char) * (len + 1));
			if (!array)
				return (NULL);
			array[i] = split_tokens(&input[start], len);
			if (!array)
				return (NULL);
			i++;
		}
		array[no_tokens] = NULL;
	}
	else
	array = ft_split(input, ' ');
	if (!array)
		return (NULL);
	return (array);
}
