/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 13:52:00 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/11 14:48:17 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static t_command	*handle_commands(t_parser *tokens, int flag)
{
	t_command		*cmds;

	cmds = (t_command *)malloc(sizeof(t_command));
	if (!cmds)
		exit(EXIT_FAILURE); // fix this later
	init_cmd_struct(cmds);
	tokens->cmd_list = tokens->input;
	cmds->input = tokens->cmd_list;

	// the one that must be a cmd
	if (flag == 0)
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
	printf("(reds)tokens->input: [%s]\n", tokens->input);
	tokens->redirect_list = tokens->input;
	printf("(reds)tokens->redirect_list: [%s]\n", (char *)tokens->redirect_list);
	reds->input = tokens->redirect_list;
	printf("(reds)reds->input: [%s]\n", reds->input);
	reds->meta = reds->input;
	printf("(reds)reds->meta: [%s]\n", reds->meta);

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
	t_command		*cmds = NULL;
	t_redirect		*reds = NULL;
	int				flag = 0;
	int				re = 0;
	int				cmd = 0;

	token_list = tokens;
	while (token_list)
	{
		if (is_redirect(token_list))
		{
			// put reds in struct
			reds = handle_redirect(token_list);
			token_list->redirect_list = reds; 
			printf("token->red->meta = [%s]\n", token_list->redirect_list->meta);
		}
		// if there was a redirect, need to check which so that if >, next node is file, 
		// and if pipe, next is command ( don't use index anymore, just keep for first arg)
		// so.... if (there was a sassy red and i need to do something with next node) ...
		else
		{
			// puts rest in command struct as cmd or str
			cmds = handle_commands(token_list, flag);
			token_list->cmd_list = cmds;
			printf("token->cmd->cmd = [%s]\n", token_list->cmd_list->cmd);
			printf("token->cmd->strs = [%s]\n", token_list->cmd_list->strs);
		}
		token_list = token_list->next;
		flag++;
	}
	printf("re: [%i]\ncmd: [%i]\n", re, cmd);
	return (tokens);
}

