/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/12 17:24:16 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * after:
 * spaces are parsed
 * quotes are found
 * redirects are found
 * delimiters are found
 * 
 * FIND dollar and word or dollar + ?
 * FIND buildins + flags are found
 * FIND ALL OTHER INPUT input
 */
// char *find_tokens(char *input)
// {
// 	int		i;
// 	char	*dollar;

// 	i = 0;
// 	dollar = NULL;
// 	// while (input[i])
// 	// {	
// 	// 	while !quote, !pipes, !dollars, !arrows, !flags...
// 	// 	then find, else ill loose the string before these finds and cut the find away from the rest of the string
// 	// 	if (ft_isdollar(input[i]))
// 	// 	{
// 	// 		dollar = find_dollar(&input[i]);
// 	// 		printf("dollar: %s\n", dollar);
// 	// 		if (!dollar)
// 	// 			return (0);
// 	// 		return (dollar);
// 	// 	}
// 	// 	find build ins
// 	// 	find strings
// 	// 	i++;
// 	// }
// 	return (0);
// }

/**
 * parse spaces, finds quoted tokens, redirects, and delimiters
 * then parse rest to find dollars, built in, string input...
 * 
*/
char	*parse_token(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	parse_space(input);
	if (!closed_quotes(input))
		return (0);
	// while (input[i])
	// {	
	// 	// if (find_quotes(input))
	// 	// 	return (input);
	// // 	// else if (find_redirects(input))
	// // 	// 	return (input);
	// // 	// else if (find_delimiter(input))
	// // 	// 	return (input);
	// // 	if (find_tokens(&input[i]))
	// // 	{
	// // 		printf("parse_token input: %s\n", &input[i]);
	// // 		return (&input[i]);
	// // 	}
	// 	i++;
	// }
	// return (0);
	return (input);
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
		parsed_token = parse_token(input);
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
