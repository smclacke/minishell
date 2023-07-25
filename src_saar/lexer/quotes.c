/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 17:07:01 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/25 23:25:02 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * bleh, probably use this in parser instead of lexer
*/
int	sign_tokens(char *input)
{
	int		i = 0;
	while (input[i])
	{
		if (ft_strcmp(&input[i], "$") == 0)
			return (DOLLAR);
		else if (ft_strcmp(&input[i], ">>") == 0)
			return (MOREMORE);
		else if (ft_strcmp(&input[i], ">") == 0)
			return (MORE);
		else if (ft_strcmp(&input[i], "<<") == 0)
			return (LESSLESS);
		else if (ft_strcmp(&input[i], "<") == 0)
			return (LESS);
		else if (ft_strcmp(&input[i], "|") == 0)
			return (PIPE); 
		i++;
	}
	return (0);
}

/**
 * get full quoted string from first to last quotations in whole input
 * make substr, return it to parse_input
*/
char	*quote_tokens(char *input)
{
	char	*quote_strs = NULL;
	int		i = 0;

	while (input[i])
	{
		if (input[i] == '\'' && closed_quotes(&input[i]))
			quote_strs = &input[i + closed_quotes(&input[i])];
		if (input[i] == '\"' && closed_quotes(&input[i]))
			quote_strs = &input[i + closed_quotes(&input[i])];
		i++;
	}
	return (quote_strs);
}

/**
 * check if double or single, count amount for each, check if divisable by 2 (thus closed)
*/
int	closed_quotes(char *input)
{
	int	i;
	int	count_double;
	int	count_single;

	i = 0;
	count_double = 0;
	count_single = 0;
	while (input[i])
	{
		if (ft_isdouble_q(input[i]))
			count_double++;
		i++;
	}
	i = 0;
	while (input[i])
	{
		if (ft_issingle_q(input[i]))
			count_single++;
		i++;
	}
	if ((count_double % 2) != 0 || (count_single % 2) != 0)
		return (0); // ERROR HERE ...  and quit (?)
	return (i);
}

/**
 * find quotes, return substring from first quote to last quote in the input (not necessarily 
 * the pair of quotes, will handle this properly in parser)
 * if unclosed, throw error
*/
char	*check_quotes(char *input)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = ft_strlen(input);
	while (len > 0)
	{
		if (ft_isquote(input[len]))
		{
			ret = ft_substr(input, i, len + 1);
			if (!ret)
				return (0);
			return (ret);
		}
		--len;
	}
	return (0); // ERROR HERE ...  and quit (?)
}
