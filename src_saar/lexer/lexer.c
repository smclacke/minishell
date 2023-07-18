/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/18 18:46:55 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 *	get size of string, create substring to pass back to lexer as newly made token
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
t_lexer	*lexer(char *input)
{
	char		*new_token;
	int			i;
	t_lexer		*token;
	t_lexer		*token_list = NULL;

	i  = 0;
	while (input[i])
	{
		new_token = make_token(input);
		if (!new_token)
			return (0);
		token = list_new(new_token);
		if (!token)
			return (0);
		listadd_back(&token_list, token);
		i++;
	}
	return (token);
}

/**
 * make a 2D array of the input, split anything in quotes into one string and everything else
 * via spaces into separate strings, give to the lexer to make tokens and pass token list back to main
*/
char	**split_input(char *input)
{
	char	**array;

	array = NULL;

	// hit space/redirects/quote...
	// handle quotes, ensure they are closed, add as part of array (at that index)

	return (array);
}
/**
 * just spaces for when nothing goes right and i need to just see some tokens
 * for mental health :)
*/
char	**parse_input(char *input)
{
	char	**array;

	array = ft_split(input, ' ');
	return (array);
}

// STOOOOOOOOOOPID :) :) :) :)
// WHEN HOW WHAT ERROR HANDLING.... ERRRM don't just return 0 :')
