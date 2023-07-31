/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/01 01:28:28 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

static bool	parser_cmp(t_lexer *tokens, t_parser  *parser_struct)
{
	if (parser_cmp_signs(tokens)) // still need to check if there are chars before/ after that are invalid...
	{	// why does   bc$USR fail and $USR succeed? this is good but why??
		parser_struct->sign = tokens->input;
		printf("first->sign: %s\n", parser_struct->sign);
		return (true);
	}
	else if (parser_cmp_builtins(tokens))
	{
		parser_struct->cmd = tokens->input;
		printf("first->cmd: %s\n", parser_struct->cmd);
		return (true);
	}
	else if (parser_cmp_abso(tokens))
	{
		parser_struct->abso = tokens->input; // will at some point need to validate the paths...
		printf("first->abso: %s\n", parser_struct->abso);
		return (true);	
	}
	return (false);
}

/**
 * compare the first token to cmds and valid signs
*/
static bool	parser_first_token(t_lexer *tokens, t_parser *parser_struct)
{
	t_lexer	*tmp;

	tmp = tokens;
	if (parser_check_quotes(tmp))
	{
		tmp->input = remove_quotes(tmp);
		if (!tmp->input)
			return (0);
		if (parser_cmp_builtins(tmp))
		{
			tokens->input = tmp->input;
			parser_struct->cmd = tokens->input;
			printf("first->cmd: %s\n", parser_struct->cmd);
			return (true);
		}
	}
	else
		if (parser_cmp(tokens, parser_struct))
			return (true);
	return (false);
}

/**
 * puts each token into parser struct as:  
 * sign, pipe, builtin, abso or just str
 * printing each for testing purposes
 * 			ALSO NEED TO REMOVE QUOTES FOR ALL OTHER INPUT IF CMD, BUT TEST THIS FULLY
*/
static void	*parser_define_tokens(t_lexer *tokens, t_parser *parser_struct)
{
	if (parser_cmp_signs(tokens))
	{
		parser_struct->sign = tokens->input;
		printf("second->sign: %s\n", parser_struct->sign);
	}
	else if (ft_strnstr(tokens->input, "|", 1) == 0)
	{
		parser_struct->sign = tokens->input;
		printf("second->sign: %s\n", parser_struct->sign);
	}
	else if (parser_cmp_builtins(tokens))
	{
		parser_struct->cmd = tokens->input;
		printf("second->cmd: %s\n", parser_struct->cmd);
	}
	else if (parser_cmp_abso(tokens))
	{	
		parser_struct->abso = tokens->input;
		printf("second->abso: %s\n", parser_struct->abso);
	}
	else
	{
		parser_struct->str = tokens->input;
		printf("second->str: %s\n", parser_struct->str);
	}
	return (0);
}

/**
 * main parser function
 * check the first one if cmd/redirect/here_doc
 * check all other tokens if valid
 * if good, define what it is within struct, will need to do most parsing here
 * return parsed tokens to main for expander
*/
t_parser	*parser(t_lexer *tokens)
{
	t_parser	*parser_struct;
	t_lexer		*list;

	parser_struct = (t_parser *)malloc(sizeof(t_parser));
	if (!parser_struct)
		return (0);
	if (!parser_first_token(&tokens[0], parser_struct))
		return (0);
	tokens = tokens->next;
	list = tokens;
	while (list)
	{
		parser_define_tokens(list, parser_struct);
		list = list->next;
	}
	return (parser_struct);
}

