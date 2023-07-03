/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/03 15:46:25 by smclacke      ########   odam.nl         */
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
		printf("token: %s\n", list->input);
		list = list->next;
	}
	return (token);
}

// parse space
void	parse_space(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
}

// check if |, >, <, >>, <<, return correct index to token_len
// is redirct, i.e. token itself
int	is_token(char *str)
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


int		token_len(char *input)
{
	int	i;
	
	i = 0;
	while (input[i])
		i++;
	// if (is_token(&input[i]))					// if input is is_token, return
	// 	return (is_token(&input[i]));
	// while (!ft_isspace(input[i]) && input[i] && !is_token(input[i]))	// while !spaces, there is input and input is not already a token
	// if is_quote
	// find next quote + add index (second_quote)
	return (i);
}

char	*make_token(char *input)
{
	char	*type;
	int		len;

	len = token_len(input);			
	printf("token len: %d\n", len);				// get size of token
	printf("input in make token: %s\n", input);
	type = ft_substr(input, 0, len);			// create substring of input, 0, len == type
												// add token length on to input (?)
	return (type);
}

t_lexer	*lexer(char *input)
{
	char	*input_token;
	t_lexer	*token;
	t_lexer	*node;
	
	token = NULL;
	node = NULL;
	// while (*input)
	// {
		parse_space(&input);							// remove spaces from input
		input_token = make_token(input);				// make token out of input
		token = (t_lexer *)ft_lstnew(input_token); 		// create node in list with newly created token
		ft_lstadd_back((t_list **)&token, (t_list *)node); 					// add node to lstadd_back
	// }
	return (token);
}
