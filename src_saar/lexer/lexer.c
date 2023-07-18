/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/18 20:01:04 by smclacke      ########   odam.nl         */
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
	char	*string; // don't know if I need this
	int		i = 0;

// going to split the input, find shit i need, make string out of it, put all string into an array 
// think about e'ch'o some"thing"some = somethingsome
// also don't want to go straight to quotes, so if quote found + one before is not space...
	array = NULL;

	while (input[i])
	{
		while (ft_isalnum(input[i]))
			i++;
		if (ft_isspace(input[i]))
		{
			// add index 0 - i into array
			return (42);
		}
		else if (ft_isquote(input[i]))
		{
			// find closing quote THAT MATCH :)
			// error if not closed
			// take everything from this point to closing quote
			// check if the one before the first quote is not a space...
			// if so, go back and take everything up until sign or space
			// add to array
			return (42);
		}
		else if (ft_ispipe(input[i]))
		{
			// add current char as string in array
			return (42);	
		}
		else if (ft_isdollar(input[i]))
		{
			// take everything after it up to a space/quote/dollar/pipe...
			// make string for array
			return (42);
		}
		else if (ft_ismore(input[i]))
		{
			// check if it is one or two more than's
			// take words after (including if theres a space between sign and word)
			// string string string
			return (42);
		}
		else if (ft_isless(input[i]))
		{
			// check if it is one or two less than's
			// take words after (including if theres a space between sign and word)
			// string string string
			return (42);
		}
		
			
	}
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
