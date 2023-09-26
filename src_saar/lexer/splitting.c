/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/26 15:35:14 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static int	start_token(char *input, int old_start)
{
	int 	j = 0;
	char	*quote_type = NULL;

	while (input[old_start] && ft_isspace(input[old_start]))
		old_start++;
	j = old_start;
	while (input[old_start] && !ft_isspace(input[old_start]))
	{
		if (ft_ismeta(input[old_start]))
			return (j);
		if (ft_isquote(input[old_start]))
		{
			quote_type = which_quote(&input[old_start]);
			old_start += next_quote(&input[old_start], *quote_type);
		}
		old_start++;
	}
	return (j);
}

static int	len_token(char *input, int len)
{
	int		j = 0;
	char	*quote_type = NULL;

	while (input[len] && ft_isspace(input[len]))
		len++;
	j = len;
	while (input[len] && !ft_isspace(input[len]))
	{	
		if (ft_ismeta(input[len]))
		{
			len += which_meta(&input[len]);
			len = len - j;
			return (len);
		}
		if (ft_isquote(input[len]))
		{
			quote_type = which_quote(&input[len]);
			len += next_quote(&input[len], *quote_type);
		}
		len++;
	}
	len = len - j;
	return (len);	
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
		count++;
		if (ft_ismeta(input[i]))
		{
			if (ft_strnstr(input, MOREMORE, 2) || ft_strnstr(input, LESSLESS, 2))
				i++;
			count++;
			i++;
		}
		while (input[i] && !ft_isspace(input[i]))
		{
			if (ft_isquote(input[i]))
			{
				quote_type = which_quote(&input[i]);
				i += next_quote(&input[i], *quote_type);
			}
			i++;
		}
	}
	return (count);
}

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
			printf("start = %i\n", start);
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
