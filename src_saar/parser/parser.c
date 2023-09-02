/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/02 20:58:46 by smclacke      ########   odam.nl         */
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
		tokens->redirect_list = tokens->input;
		return (true);
	}
	return (false);
}

// put input into redirect_list, if file is attached, detach and add file to
// file part of struct
// if not attached, add next node into file part of struct
static void	handle_redirect(t_parser *tokens)
{
	// int	i = 0;

	if (!tokens)
		exit(EXIT_FAILURE); // dunno, so something when error handling
	// if (tokens->redirect_list->meta_type == E_PIPE)
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

// first part in cmd, rest in strs
static void	handle_commands(t_parser *tokens)
{
	// t_command	*commands;
	t_parser		*tmp;

	tmp = tokens;
	tmp->cmd_list = tmp->input;
	tmp->cmd_list->strs = tmp->cmd_list;
	// commands = tokens->cmd_list;
	// while (tmp)
	// {
	// 	tmp->cmd_list->strs = tmp->cmd_list;
	// 	tmp->cmd_list = tmp->next->cmd_list;
	// }
}

static bool	file_attached(t_parser *tokens)
{
	if (!tokens)
		return (false);
	if (ft_strcmp(tokens->input, ">>") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, "<<") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, ">") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, "<") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, "|") == 0)
		return (true);
	return (false);
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
		{
			if (!file_attached(token_list))
			{
				token_list->redirect_list = token_list->next->input;
				token_list = token_list->next;
			}
			handle_redirect(token_list);
		}
		else
			handle_commands(token_list);
		token_list = token_list->next;
	}
	return (tokens);
}
