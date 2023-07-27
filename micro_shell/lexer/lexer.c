/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 14:44:51 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/27 18:51:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**micro_parse_input(char *input)
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

static t_lexer	*micro_make_token_list(char **parsed_input)
{
	t_lexer		*token_list = NULL;
	t_lexer		*token;
	char		*token_str;
	int			len;
	int			i = 0;

	while (&parsed_input[i])
	{
		printf("parsed_input: %s\n", parsed_input[i]);
		i++;
	}
	while (parsed_input[i] && parsed_input)
	{
		printf("are you ok?\n");
		len = ft_strlen(parsed_input[i]);
		token_str = ft_substr(parsed_input[i], 0, len + 1);
		if (!token_str)
			return (0);
		token = micro_lexer_listnew(token_str);
		if (!token)
			return (0);
		micro_lexer_listadd_back(&token_list, token);
		i++;
	}
	return (token_list);
}

t_lexer	*micro_lexer(char *input)
{
	t_lexer		*token_list;
	char		**parsed_input;
	int			i;

	i  = 0;
	while (input[i])
	{
		parsed_input = micro_parse_input(input);
		if (!parsed_input)
			return (0);
		i++;
	}
	i = 0;
	token_list = micro_make_token_list(parsed_input);
	if (!token_list)
		return (0);
	return (token_list);
}
