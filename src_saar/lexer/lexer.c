/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/16 18:22:34 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

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
t_lexer *lexer(char *input)
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
char	**parse_input(char *input)
{
	char	**array;
	char	*temp_quote;
	char	*temp_redir;
	int		i;

	i = 0;

	// quote: handle and create substring, add to final array
	// check for redirects, create separate string to add to array
	// for checking for quotes and symbols, I need to keep the correct index!
	array = NULL;
	while (input[i] && !ft_isquote(input[i])) // && is not redir/delimit
	{
		array = ft_split(input, ' ');
		i++;
	}
	if (ft_isquote(input[i]))
	{
		temp_quote = check_quotes(&input[i]);
		if (!temp_quote)
			return (0);
	}
	// strjoin temp_quote to array at correct index
	// check for redirs + delimiters
	// strjoin those new string to array at correct index 
	// check everything other than inside quotes for symbols, they need to be separate tokens
	return (array);
}


// STOOOOOOOOOOPID :) :) :) :)
// WHEN HOW WHAT ERROR HANDLING.... ERRRM don't just return 0 :')
