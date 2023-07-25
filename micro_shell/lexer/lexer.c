/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 14:44:51 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/25 16:39:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// check_meta - return the enum for which char it is
int	micro_sign_tokens(char *input)
{
	int		i = 0;
	while (input[i])
	{
		if (ft_strcmp(&input[i], "$") == 0)
			return (DOLLAR);
		else if (ft_strcmp(&input[i], ">>") == 0)
			return (MOREMORE);
		else if (ft_strcmp(&input[i], ">") == 0)
			return (MORE);
		else if (ft_strcmp(&input[i], "<<") == 0)
			return (LESSLESS);
		else if (ft_strcmp(&input[i], "<") == 0)
			return (LESS);
		else if (ft_strcmp(&input[i], "|") == 0)
			return (PIPE); 
		i++;
	}
	return (0);
}


// check_quote - single quotes inside characters = remove them

// parse func
static char	**micro_parse_input(char *input)
{
	char	**array = NULL;
	// int		i = 0;


	// we can still split on space BUT, check first for quotes, handle
	// 	them differently, with a quote split func maybe?
	// leave the meta_char check for the parser?
	array = ft_split(input, ' ');
	// while (input[i])
	// {
	// 	if (micro_sign_tokens(&input[i]))
	// 		return (&input[i]);
	// 	i++;
	// }
	return (array);
}

static t_lexer	*micro_make_token_list(char **parsed_token)
{
	t_lexer		*token_list = NULL;
	t_lexer		*token;
	char		*token_str;
	int			i = 0;
	int			len = 0;

	while (parsed_token[i])
	{
		len = ft_strlen(parsed_token[i]);
		printf("length: %i\n", len);
		token_str = ft_substr(parsed_token[i], 0, len + 1);
		if (!token_str)
			return (0);
		printf("token_str: %s\n", token_str);
		token = micro_lexer_listnew(token_str);
		if (!token)
			return (0);
		micro_lexer_listadd_back(&token_list, token);
		i++;
	}
	return (token_list);
}

t_lexer	*ft_micro_lexer(char *input)
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
	while (parsed_input[i])
	{
		printf("parsed input: %s\n", parsed_input[i]);
		i++;
	}
	token_list = micro_make_token_list(parsed_input);
	if (!token_list)
		return (0);
	return (token_list);
}
