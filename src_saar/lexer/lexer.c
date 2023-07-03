/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/03 18:24:24 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/*
	after spaces are parsed, no quotes or redirects are found, find words and symbols
	dollar and word
	whole flag
*/
char *find_tokens(char *input)
{
	
}

/*
	parse spaces, finds quoted tokens, words, redirects, symbols...
	- if redirect is found, return to lexer
	- if quote + contents + closing quote found, return to lexer...
	- else find word, flag or symbol from find_tokens,
	pass it back to lexer to create new token node in list
*/
char	*parsing_token(char *input)
{
	parse_spaces(&input);
	if (find_quotes(&input))
		return (input);
	else if (find_redirects(&input))
		return (input);
	else if (find_delimiter(&input))
		return (input);
	else
		if (find_tokens(&input))
			return (input);
	return (0);
}

/*
	get size of string, create substring to pass backto lexer as newly made token
*/

char	*make_token(char *parsed_token)
{
	char	*token;
	int		len;

	len = token_len(parsed_token);	
	token = ft_substr(parsed_token, 0, len);
	return (token);
}

/*
	take input, parse through spaces, quotes, redirects, words and symbols
	find thing to tokenise, pass to make_token() to create a substr of it with the correct length
	create new node in list for the newly made token
	add node to end of list
	///
	pass new listed token to parser, with quotes attached so that the parser can differentiate between double and single
	also, if dollar, take word after too as token, if flag, take whole thing... anymore things to think about.... (?)
	///
	!!! take argv[i], keep parsing till NULL because argv[i] could contain multiple tokens
	!!! return made token but need to keep parsing rest of argv[i] in lexer...
	!!! do I even need to return, if a list of tokens is created....
*/

t_lexer	*lexer(char *input)
{
	char		*new_token;
	char		*parsed_token;
	t_lexer		*token;
	t_lexer		*node;
	int			i;

	i  = 0;
	while (input[i])
	{
		node = NULL;
		parsed_token = parsing_token(&input);
		if (!parsed_token)
			return (0); //!
		new_token = make_token(parsed_token);
		if (!new_token)
			return (0); //!
		token = (t_lexer *)ft_lstnew(new_token);
		if (!token)
			return (0); //!
		ft_lstadd_back((t_list **)&token, (t_list *)node);
		return (token);
		i++;
	}
	return (0); //!
}

// WHEN HOW WHAT ERROR HANDLING.... ERRRM don't just return 0 :')
