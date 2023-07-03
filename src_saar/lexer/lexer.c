/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/03 15:05:00 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

// print tokens for testing
t_lexer	*ft_print_tokens(t_lexer *token)
{
	t_lexer	*list;

	list = token;
	while (list)
	{
		printf("token: %d\n", list->var);
		list = list->next;
	}
	return (token);
}

// parse space
void	parse_space(const char **input)
{
	while (ft_isspace(**input))
		(*input)++;
}

// find next quotation
int	second_quote(const char *input, char c)
{
	int	i;

	i = 1;
	while (input[i] != c && input[i])
		i++;
	return (i);
}

// check if |, >, <, >>, <<, return correct index to token_len
// is redirct, i.e. token itself
int	is_token(const char *str)
{
	if (*str == '<' || *str == '>')
	{
		if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
			return (2);
		return (1);
	}
	else if (*str == '|')
		return (1);
	return (0);
}


int		token_len(const char *input)
{
	int	i;
	
	i = 0;
	if (is_token(&input[i]))					// if input is is_token, return
		return (is_token(&input[i]));
	// while !spaces, there is input and input is not already a token
	// if is_quote
	// find next quote + add index (second_quote)
	return (i);
}

char	*make_token(const char **input)
{
	char	*type;
	int		len;

	len = token_len(*input);					// get size of token
	type = ft_substr(*input, 0, len);			// create substring of input, 0, len == type
												// add token length on to input (?)
	return (type);
}

t_lexer	*lexer(const char *input)
{
	char	*input_token;
	t_lexer	*token;
	t_lexer	*node;
	
	token = NULL;
	node = NULL;
	while (*input)
	{
		parse_space(&input);							// remove spaces from input
		input_token = make_token(&input);				// make token out of input
		token = (t_lexer *)ft_lstnew(input_token); 		// create node in list with newly created token
		ft_lstadd_back((t_list **)&token, (t_list *)node); 					// add node to lstadd_back
	}
	return (token);
}
