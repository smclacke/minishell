/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/01 17:04:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

static bool	parser_redirect(t_parser *tokens)
{
	if (!tokens)
		return (false);
	if (ft_strnstr(tokens->input, ">>", 2))
		return (true);
	else if (ft_strnstr(tokens->input, "<<", 2))
		return (true);
	else if ((ft_strnstr(tokens->input, ">", 1)))
		return (true);
	else if (ft_strnstr(tokens->input, "<", 1))
		return (true);
	else if ((ft_strnstr(tokens->input, "|", 1)))
	{
		tokens->redirect_list->meta_type = PIPE;
		return (true);
	}
	return (false);
}

static void	handle_direct(t_parser *tokens)
{
	if (!tokens)
		return (1);
	if (tokens->redirect_list->mext_type = PIPE)
		return ;
	else
	{
		while (tokens[i])
		{
			// if ()
			printf("here\n");
		}	
	// check if file is attached to redirect, if not do next line, oherwise...
	// separate redirect from file and then initalise them separately in redirects list
		// tokens->redirect_list->file = tokens->next;
	}
	return (0);
}

static void	handle_commands(t_parser *tokens)
{
	tokens = tokens->cmd_list->cmd;
	prinf("testing... maybe\n");
}

/**
 * @brief	Main parser function:
			Check the tokens to see which member of the parser struct they need to be sorted into
 * @param	tokens t_lexer tokens passed from the lexer to be sorted by the parser
 * @return	parser_struct: all the tokens given by the lexer have been sorted into the parser struct
*/
t_parser	*parser(t_parser *tokens)
{
	t_parser		*token_list;

	token_list = tokens;
	while (token_list)
	{
		if (parser_redirect(token_list))
			handle_redirect(token_list);
		else
			handle_commands(token_list);
		token_list = token_list->next;
	}
	return (tokens);
}
