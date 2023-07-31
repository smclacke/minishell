/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/31 21:32:17 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

static char	**parse_input(char *input)
{
	char	**array = NULL;
	// int		i = 0;

	// while (input[i])
	// {
		// while (input not quote)
	array = ft_split(input, ' ');
	if (!array)
		return (0);
		// if input quote
		// 	do something about it
	// 	i++;
	// }
	return (array);
}

static t_lexer	*make_token_list(char **parsed_input)
{
	t_lexer		*token_list = NULL;
	t_lexer		*token;
	char		*token_str;
	int			len;
	int			i = 0;

	while (parsed_input[i])
	{
		len = ft_strlen(parsed_input[i]);
		token_str = ft_substr(parsed_input[i], 0, len + 1);
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

t_lexer	*lexer(char *input)
{
	t_lexer		*token_list;
	char		**parsed_input = NULL;
	int			i;

	i  = 0;
	while (input[i])
	{
		parsed_input = parse_input(input);
		i++;
	}
	i = 0;
	if (!parsed_input)
		return (0);
	token_list = make_token_list(parsed_input);
	if (!token_list)
		return (0);
	return (token_list);
}

// STOOOOOOOOOOPID :) :) :) :)
// WHEN HOW WHAT ERROR HANDLING.... ERRRM don't just return 0 :')
