/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/11 19:51:57 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/*
	after spaces are parsed, no quotes or redirects are found, find words and symbols
	dollar and word
	whole flag
*/
// char *find_tokens(char *input)
// {
	
// }

/*
	parse spaces, finds quoted tokens, words, redirects, symbols...
	- if redirect is found, return to lexer
	- if quote + contents + closing quote found, return to lexer...
	- else find word, flag or symbol from find_tokens,
	pass it back to lexer to create new token node in list
*/
char	*parsing_token(char *input)
{
	// printf("input received in parsing_toekn(): %s\n", input);
	parse_space(input);
	return (input);
	// printf("input after parse_spaces in parsing_toekn(): %s\n", input);
	// if (find_quotes(&input))
	// 	return (input);
	// else if (find_redirects(&input))
	// 	return (input);
	// else if (find_delimiter(&input))
	// 	return (input);
	// else
	// 	if (find_tokens(&input))
	// 		return (input);
	// return (0);
}


// t_stack	*node_new(int node)
// {
// 	t_stack	*new;

// 	new = malloc(sizeof(t_stack));
// 	if (!new)
// 		return (0);
// 	new->num = node;
// 	new->index = 0;
// 	new->next = NULL;
// 	return (new);
// }
// void	var_to_stack(t_stack **stack, int var)
// {
// 	t_stack	*new;
// 	t_stack	*node;

// 	if (!*stack)
// 	{
// 		*stack = node_new(var);
// 		return ;
// 	}
// 	node = *stack;
// 	while (node->next)
// 		node = node->next;
// 	new = node_new(var);
// 	node->next = new;
// }

/*
	get size of string, create substring to pass backto lexer as newly made token
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
	take input, parse through spaces, quotes, redirects, words and symbols
	find thing to tokenise, pass to make_token() to create a substr of it with the correct length
	create new node in list for the newly made token
	add node to end of list
	///
	pass new tokens to parser, with quotes attached so that the parser can differentiate between double and single
	also, if dollar, take word after too as token, if flag, take whole thing... anymore things to think about.... (?)
	///
	!!! take argv[i], keep parsing till NULL because argv[i] could contain multiple tokens
	!!! return made token but need to keep parsing rest of argv[i] in lexer...
	~~~ if the list has been made, do I still need to return each token?
	~~~ I think if the list is made and stored, I can just take that and run it through
	the parser...
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

// return ((t_lexer *)token) and giving that to print_tokens() aint it....

/*
	list
	lexer
*/



// STOOOOOOOOOOPID :) :) :) :)
// WHEN HOW WHAT ERROR HANDLING.... ERRRM don't just return 0 :')
