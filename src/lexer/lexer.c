/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/13 17:10:44 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo errors (printfs) and basic comments
*/
static int	quote_input(char *input, int i)
{
	char	*quote_type;

	while (input[i] && !space_or_meta(input[i]))
	{
		if (ft_isquote(input[i]))
		{
			quote_type = which_quote(&input[i]);
			i += next_quote(&input[i], *quote_type);
		}
		i++;
	}
	return (i);
}

static int	amount_tokens(char *input)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (ft_ismeta(input[i]))
		{
			if (ft_ismeta(input[i + 1]))
				i++;
			count++;
			i++;
		}
		if (input[i] && !ft_isspace(input[i]))
		{
			i = quote_input(input, i);
			count++;
		}
	}
	return (count);
}

static char	*split_tokens(char *input, int len)
{
	char	*token;

	if (!input)
		return (NULL);
	token = ft_substr(input, 0, len);
	if (!token)
	{
		printf("im a malloc error in the lexer\n");
		return (0);
	}
	input += len;
	return (token);
}

static char	**lexer_split(char *input)
{
	char	**array;
	int		i;
	int		start;
	int		len;
	int		no_tokens;

	i = 0;
	start = 0;
	len = 0;
	no_tokens = amount_tokens(input);
	array = (char **)malloc(sizeof(char *) * (no_tokens + 1));
	if (!array)
	{
		printf("im a malloc error in the lexer\n");
		return (0);
	}
	while (i < no_tokens)
	{
		start = start_token(input, (start + len));
		len = len_token(input, start);
		array[i] = split_tokens(&input[start], len);
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**lexer(char *input)
{
	char	**array;

	if (!input)
		return (NULL);
	if (!is_space(input))
		add_history(input);
	array = lexer_split(input);
	if (!array)
	{
		printf("im a lexer error, lexer_array()\n");
		free(input);
		return (0);
	}
	// free(input);
	return (array);
}
