/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/22 12:14:06 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 *	get size of string, create substring to pass back to lexer as newly made token
*/
static char	*make_token(char *parsed_token)
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
	t_lexer		*token;
	t_lexer		*token_list = NULL;
	int			i;

	i  = 0;
	while (input[i])
	{
		new_token = make_token(input);
		if (!new_token)
			return (0);
		token = mini_listnew(new_token);
		if (!token)
			return (0);
		mini_listadd_back(&token_list, token);
		i++;
	}
	return (token);
}

// STOOOOOOOOOOPID :) :) :) :)
// WHEN HOW WHAT ERROR HANDLING.... ERRRM don't just return 0 :')
