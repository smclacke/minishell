/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/11 21:15:47 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * after:
 * spaces are parsed
 * quotes are found
 * redirects are found
 * dollar and word or dollar + ? are found
 * buildins + flags are found
 * FIND ALL OTHER INPUT input
 */
// char *find_tokens(char *input)
// {
	
// }

/**
 * parse spaces, finds quoted tokens, words, redirects, symbols...
 * - if redirect is found, return to lexer (< > |)
 * - if quote + contents + closing quote found, return to lexer...
 * - else find word, flag or symbol from find_tokens,
 * pass it back to lexer to create new token node in list
*/
char	*parsing_token(char *input)
{
	parse_space(input);
	if (find_quotes(input))
		return (input);
	else if (find_redirects(input))
		return (input);
	else if (find_delimiter(input))
		return (input);
	else
		if (find_tokens(input))
			return (input);
	return (0);
}

/**
 *	get size of string, create substring to pass backto lexer as newly made token
*/

char	*make_token(char *parsed_token)
{
	char	*token;
	int		len;

	len = ft_strlen(parsed_token);	
	token = ft_substr(parsed_token, 0, len);
	if (!token)
		return (0);
	return (token);
}

/*
 *	take input, parse through spaces, quotes, redirects, words and symbols
 *	find thing to tokenise, pass to make_token() to create a substr of it with the correct length
 *	create new node in list for the newly made token
 *	add node to end of list
*/

t_list *lexer(char *input)
{
	char		*new_token;
	char		*parsed_token = NULL;
	int			i;
	t_list		*token;
	t_list		*token_list = NULL;

	i  = 0;
	while (input[i])
	{
		parsed_token = parsing_token(input);
		if (!parsed_token)
			return (0);
		new_token = make_token(parsed_token);
		if (!new_token)
			return (0);
		token = ft_lstnew(new_token);
		if (!token)
			return (0);
		ft_lstadd_back(&token_list, token);
		i++;
	}
	return (token);
}

// STOOOOOOOOOOPID :) :) :) :)
// WHEN HOW WHAT ERROR HANDLING.... ERRRM don't just return 0 :')
