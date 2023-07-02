/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/02 15:20:01 by SarahLouise   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

// space, tab, \n, ;, comma, <, >, |, &
// words, keywords, In / Out redirectors, semicolons
// delimiters ;, |, &

// parse space
void	parse_space(const char **input)
{
	while (ft_ispace(**input))
		(*input)++;
}

// check if |, >, <, >>, <<, return correct index to token_len
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

// find next quotation
int	second_quote(const char *input, char c)
{
	int	i;

	i = 1;
	while (input[i] != c && input[i])
		i++;
	return (i);
}

int		token_len(const char *input)
{
	int	i;
	
	i = 0;
	// if input is is_token, return
	if (is_token(&input[i]))
		return (is_token(&input[i]));
	// while !spaces, there is input and input is not already a token
	// if is_quote
	// find next quote + add index (second_quote)
	// return index
}

char	*make_token(const char **input)
{
	char	*type;
	int		len;

	// get size of token
	// create substring of input, 0, len == type
	// add token length on to input
	// return type 
}

t_list	*lexer(const char *input)
{
	char	*input_token;
	t_list	*token;
	t_list	*node;
	
	token = NULL;
	while (*input)
	{
		// remove spaces from input
		// token = make_token out of input
		// create node in list with newly created token
		// add node to lstadd_back (&token, node)
	}
	return (token);
}


// check type of symbol
/*
single quote
double quote
pipe
dollar
more than
less than
<<
>>
*/
/*

