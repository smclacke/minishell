/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/20 18:13:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// everything starts and finishes here.... let's goooooooo
		 // WE MUST SEPARATE METAS
	// split on spaces, split on metas but add metas to token array
	// if quotes, split those apart keep them totally intact
	/**
	 * while it's space, tab.... keep iterating
	 * find meta
	 * len = 1/2, 2 = same characters for next < > only
	 * if 3, third is different and should be split
	 * 
	*/ 
	

	// if (is_token(&input[i]) == 2)
	// {
	// 	// printf("&input: %s\n", &input[i]);
	// 	// printf("is meta: %i\n", is_token(&input[i]));
	// 	i++;
	// 	return (is_token(&input[i])); // BIG no no, << willl return 2 but token willbe second <
	// }
	// 	printf("token count = %i\n", count);
	// else if (is_token(&input[i]) == 1)
	// 	return (is_token(&input[i]));
	// while (input[i] && !ft_isspace(input[i])
	// 		&& !is_token(&input[i]))
	// {
	// 	if (ft_isquote(input[i]))
	// 	{
	// 		i++;
	// 		i += next_quote(&input[i], input[i]);
	// 		// printf("LT | index = %i\n", i);
	// 		return (i);
	// 	}
	// 	// printf("this is fucked\n");
	// 	i++;
	
static int	len_token(char *input, int len)
{
	int	i = 0;
	int j = 0;

	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		j = i;
		while (input[i] && !ft_isspace(input[i]))
			i++;
		len = i - j;
		// printf("len_token = %i\n", len);
		return (len);
	}
	return (0);
}

static int	start_token(char *input)
{
	int	i = 0;
	int j = 0;

	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		j = i;
		while (input[i] && !ft_isspace(input[i]))
			i++;
		return (j);	
		// printf("start_token = %i\n", j);
	}
	return (0);
}

static int	amount_tokens(char *input)
{
	int	i = 0;
	int	count = 0;

	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		count++;
		while (input[i] && !ft_isspace(input[i]))
			i++;
	}
	return (count);
}

static char	*give_tokens(char *input, int len)
{
	char	*token;

	token = ft_substr(input, 0, len);
	if (!token)
		return (NULL);
	input += len;
	return (token);
}

static bool	annoying_split(char *input)
{
	int	i = 0;
	
	if (is_meta(input))
		return (true);
	while (input[i])
	{
		if (ft_isquote(input[i]))
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
//not annoying() correctly
char	**parse_input(char *input)
{
	char	**array = NULL;
	int		no_tokens = 0;
	int		start = 0;
	int		len = 0;
	int		i = 0;

	// printf("input: %s\n", input);
	// if (annoying_split(input))
	// {
	no_tokens = amount_tokens(input);
	printf("amount of tokens: %i\n", no_tokens);
	array = (char **)malloc(sizeof(char *) * (no_tokens + 1));
	while (i < no_tokens)
	{
		len = len_token(input, len);
		printf("token len: %i\n", len);
		start = start_token(input);
		printf("start token: %i\n", start);
		array[i] = (char *)malloc(sizeof(char) * (len + 1));
		array[i] = give_tokens(&input[start], len);
		i++;
	}
	array[no_tokens] = NULL;
	// }
	// else
	// {
	// 	// printf("youre here arent you?\n");	
		// array = ft_split(input, ' ');
	// }
	if (!array)
		return (NULL);
	return (array);
	// return (0);
}
