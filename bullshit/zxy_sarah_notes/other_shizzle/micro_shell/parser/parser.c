/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:14:07 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/05 21:27:16 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// FLAGS FLAGS FLAGS
/**
 * @brief	assigns the tokens to a member in the parser struct:
 * 			meta, cmd, absolute path,  anything else str
 * @param	tokens passed from the lexer
 * @param	parser_struct  structure to assign each token to the correct member within parser struct
 * @return	assigns the token input to a member in the parser struct
*/
static void	*parser_define_tokens(t_parser *tokens)
{
	if (!tokens)
		return (false);
	if (parser_cmp_metas(tokens))
	{
		tokens->meta = tokens->input;
		printf("arg->meta: %s\n", tokens->meta);
	}
	else if (parser_cmp_builtins(tokens))
	{	
		tokens->cmd = tokens->input;
		printf("arg->cmd: %s\n", tokens->cmd);
	}
	else if (parser_cmp_abso(tokens))
	{	
		tokens->abso = tokens->input;
		printf("arg->abso: %s\n", tokens->abso);
	}
	else if (parser_cmp_squote(tokens))
	{
		tokens->squote = tokens->input;
		printf("arg->squote: %s\n", tokens->squote);
	}
	else if (parser_cmp_dquote(tokens))
	{
		tokens->dquote = tokens->input;
		printf("arg->dquote: %s\n", tokens->dquote);
	}
	else
	{
		tokens->str = tokens->input;
		printf("arg->str: %s\n", tokens->str);
	}
	return (0);
}

/**
<<<<<<< HEAD
 * @brief	Main parser function:
			Check the tokens to see which member of the parser struct they need to be sorted into
=======
 * @brief	take all tokens, put input into a temp, remove the quotes and make lowercase
 * 			test if it's a buildin, if yes, return the temp as this is valid
 * 			else, return the original input to test against signs etc
 * @param	tokens passed from lexer, being sorted and put into the parser struct
 * @param	parser_struct structure to assign each token to the correct member within parser struct
 * @return	bool: true/false 1/0   
*/
static bool	parser_format_check(t_lexer *tokens, t_parser *parser_struct)
{
	char	*tmp;

	tmp = tokens->input;
	ft_lower_str(tmp);
	if (parser_check_quotes(tokens->input))
	{
		tmp = remove_quotes(tokens->input);
		if (!tmp)
			return (0);
		if (parser_cmp_char_builtins(tmp))
		{
			parser_struct->cmd = tmp;
			printf("format_check->cmd: %s\n", parser_struct->cmd);
			return (true);
		}
	}
	return (false);
}

void	init_parser(t_parser *parser_struct)
{
	parser_struct->cmd_list = NULL;
	parser_struct->redirect_list = NULL;
	// parser_struct->str = NULL;
	// parser_struct->cmd = NULL;
	// parser_struct->sign = NULL;
	// parser_struct->abso = NULL;
}

/**
 * @brief	Main parser function: check vadility of first token
			Check the rest of the tokens to see which member of the parser struct they need to be sorted into
>>>>>>> sarah
			Return the new parser_struct to the expander
 * @param	tokens t_lexer tokens passed from the lexer to be sorted by the parser
 * @return	parser_struct: all the tokens given by the lexer have been sorted into the parser struct. The first argument is checked for its validity
*/
t_parser	*parser(t_parser *tokens)
{
	t_parser		*list;

	list = tokens;
	while (list)
	{
		// if quotes, handle separately..
		parser_define_tokens(list);
		list = list->next;
	}
	return (tokens);
}
