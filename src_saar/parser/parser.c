/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/01 17:38:57 by smclacke      ########   odam.nl         */
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
		// tokens->redirect_list->meta_type = PIPE;
		return (true);
	}
	return (false);
}

static void	handle_redirect(t_parser *tokens)
{
	// int	i = 0;

	if (!tokens)
		exit(EXIT_FAILURE); // dunno, so something when error handling
	// if (tokens->redirect_list->meta_type == PIPE)
	// 	return ;
	// else
	// {
		printf("test\n");
		// while (tokens[i])
		// {
			// if ()
			
		// }	
	// check if file is attached to redirect, if not do next line, oherwise...
	// separate redirect from file and then initalise them separately in redirects list
		// tokens->redirect_list->file = tokens->next;
	// }
}

static void	handle_commands(t_parser *tokens)
{
	// tokens->input = tokens->cmd_list->cmd;
	printf("testing... maybe\n");
}

static void	*define_tokens(t_parser *tokens)
{
	if (parser_redirect(tokens))
		handle_redirect(tokens);
	else
		handle_commands(tokens);
	return (0);
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
		define_tokens(token_list);	
		token_list = token_list->next;
	}
	return (tokens);
}
