/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 14:44:51 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/25 15:15:17 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// check_meta - return the enum for which char it is
static int	micro_sign_tokens(char *input)
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

// check_quote - single quotes, inside characters, remove them

// parse func
static char	*micro_parse_input(char *input)
{
	int		i = 0;
	
	while (input[i])
	{
		if (micro_sign_tokens(&input[i]))
			return (&input[i]);
		i++;
	}
	return (0);
}

static char	*micro_make_token(char *parsed_token)
{
	char	*token;
	int		len;

	len = ft_strlen(parsed_token);
	token = ft_substr(parsed_token, 0, len);
	if (!token)
		return (0);
	return (token);
}

t_lexer	*ft_micro_lexer(char *input)
{
	char		*new_token;
	char		*parsed_input;
	t_lexer		*token;
	t_lexer		*token_list = NULL;
	int			i;

	i  = 0;
	while (input[i])
	{
		parsed_input = micro_parse_input(input);
		if (!parsed_input)
			return (0);
		new_token = micro_make_token(parsed_input);
		if (!new_token)
			return (0);
		token = micro_lexer_listnew(new_token);
		if (!token)
			return (0);
		micro_lexer_listadd_back(&token_list, token);
		i++;
	}
	return (token);
}




