/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/05 13:40:41 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static int	quote_input(char *input, int i)
{
	char	*quote_type;

	while (input[i] && !space_or_meta(input[i]))
	{
		if (ft_isquote(input[i]))
		{
			quote_type = which_quote(&input[i]);
			if (next_quote(&input[i], *quote_type) == E_STOP)
				return (E_STOP);
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
			if (quote_input(input, i) == E_STOP)
				return (E_STOP);
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
		malloc_error(NULL, NULL, NULL, 0);
	input += len;
	return (token);
}

static char	**lexer_split(char **array, char *input, int no_tokens)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	len = 0;
	while (i < no_tokens)
	{
		start = start_token(input, (start + len));
		if (len_token(input, start) == E_STOP)
			return (NULL);
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
	int		no_tokens;
	char	*q;

	q = NULL;
	if (!input)
		return (NULL);
	if (meta_check(input, q, 0, 0) == E_STOP)
		return (NULL);
	if (amount_tokens(input) == E_STOP)
		return (NULL);
	no_tokens = amount_tokens(input);
	array = (char **)malloc(sizeof(char *) * (no_tokens + 1));
	if (!array)
		malloc_error(NULL, NULL, NULL, 0);
	array = lexer_split(array, input, no_tokens);
	if (!array)
		return (NULL);
	return (array);
}
