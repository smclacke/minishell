/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/07 12:36:10 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

static t_command	*handle_commands(t_parser *tokens, int i)
{
	t_command		*cmds;
		
	cmds = (t_command *)malloc(sizeof(t_command));
	if (!cmds)
		exit(EXIT_FAILURE); // fix this later
	init_cmd_struct(cmds);
	tokens->cmd_list = tokens->input;
	cmds->input = tokens->cmd_list;

	// the one that must be a cmd
	if (i == 0)
		cmds->cmd = cmds->input;
	else
		cmds->strs = cmds->input;
	return (cmds);
}

static t_redirect	*handle_redirect(t_parser *tokens)
{
	t_redirect	*reds;

	reds = (t_redirect *)malloc(sizeof(t_redirect));
	if (!reds)
		exit(EXIT_FAILURE); // fix this later
	init_red_struct(reds);
	tokens->redirect_list = tokens->input;

	// printf("tokens->redirect_list: [%s]\n", (char *)tokens->redirect_list);
	
	reds->input = tokens->redirect_list;

	// printf("reds->input: [%s]\n", reds->input);

	reds->meta = reds->input;

	printf("reds->meta: [%s]\n", reds->meta);
	
	return (reds);
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
	t_command		*cmds;
	t_redirect		*reds;
	int				i = 0;

	token_list = tokens;
	while (token_list)
	{
		if (is_redirect(token_list))
		{
			// put reds in struct
			reds = handle_redirect(token_list);
			token_list->redirect_list = reds;
			printf("toen->red->meta = [%s]\n", (char *)token_list->redirect_list->meta);
		}
		// if there was a redirect, need to check which so that if >, next node is file, 
		// and if pipe, next is command ( don't use index anymore, just keep for first arg)

		
		// if (there was a sassy red and i need to do something with next node) ...

		
		else
		{
			cmds = handle_commands(token_list, i);
			token_list->cmd_list = cmds;
			printf("token->cmd->cmd = [%s]\n", (char *)token_list->cmd_list->cmd);
			printf("token->cmd->strs = [%s]\n", (char *)token_list->cmd_list->strs);
		}
		token_list = token_list->next;
		i++;
	}
	return (tokens);
}

