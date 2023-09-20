/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/20 19:33:39 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static int	len_token(char *input, int len)
{
	int j = 0;

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

/**
 * @brief	takes the input string from the command line, iterates through it. While there
 * 			are no quotations, the string is split on spaces with metas (exc. dollar) also being 
 * 			split into separate str. If a quotation is encountered, the matching quote is found and
 * 			all of that input is put into token
 * @param	input input from the command line
 * @return	2D array of separated strings made from the input, ready to be tokenized
*/
//not recognising pipes correctly
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
		printf("amount of tokens: %i\n", no_tokens);
		array = (char **)malloc(sizeof(char *) * (no_tokens + 1));
		while (i < no_tokens)
		{
			start = start_token(input, (start + len));
			len = len_token(input, start);
			array[i] = (char *)malloc(sizeof(char) * (len + 1));
			array[i] = give_tokens(&input[start], len);
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
