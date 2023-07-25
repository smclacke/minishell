/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/25 23:28:06 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

// write new uselful comments....


static char	**parse_input(char *input)
{
	char	**array = NULL;
	
	// split on spaces unless quote is found, IF QUOTE IS SURROUNDED BY SPACES, take first to last quote, 
	// substr, add to array, then check if end of array or not,
	// if not, keep splitting on spaces
	array = ft_split(input, ' ');
	if (!array)
		return (0);
	return (array);
}

/**
 *	get size of string, create substring to pass back to lexer as newly made token
*/
static t_lexer	*make_token(char **parsed_token)
{
	t_lexer	*token_list = NULL;
	t_lexer	*token;
	char	*token_str;
	int		len;
	int		i = 0;

	while (parsed_token[i])
	{
		len = ft_strlen(parsed_token[i]);
		token_str = ft_substr(parsed_token[i], 0, len + 1);
		if (!token_str)
			return (0);
		token = lexer_listnew(token_str);
		if (!token)
			return (0);
		lexer_listadd_back(&token_list, token);
		i++;
	}
	return (token_list);
}

/*
 *	take input, parse through spaces, quotes, redirects, words and symbols
 *	find thing to tokenise, pass to make_token() to create a substr of it with the correct length
 *	create new node in list for the newly made token
 *	add node to end of list
*/
t_lexer	*lexer(char *input)
{
	t_lexer		*token_list;
	char		**parsed_input;
	int			i;

	i  = 0;
	while (input[i])
	{
		parsed_input = parse_input(input);
		if (!parsed_input)
			return (0);
		i++;
	}
	i = 0;
	token_list = make_token(parsed_input);
	if (!token_list)
		return (0);
	return (token_list);
}

// STOOOOOOOOOOPID :) :) :) :)
// WHEN HOW WHAT ERROR HANDLING.... ERRRM don't just return 0 :')
