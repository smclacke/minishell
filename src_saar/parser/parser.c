/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/05 18:07:17 by SarahLouise   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * function for when redirect is attached (no space) to file
 * separate from file, put redirect and file nodes into correct part of redir struct 
*/
// IF THIS FUNCTION RETURNS, THEN FILE IS SEPARATE AND WE TAKE THE NEXT NODE IN PARSER()
// static int	handle_redirect(t_parser *tokens)
// {
// 	t_redirect	*redirects;
// 	t_parser	*tmp;
// 	// t_parser	*reds;

// 	tmp = tokens;
// 	// reds = tokens->redirect_list;

// 	redirects = (t_redirect *)malloc(sizeof(t_redirect));
// 	if (!redirects)
// 		exit(EXIT_FAILURE); // fix this later

// 	if (!file_attached(tokens))
// 	{
// 		tokens->redirect_list = tokens->input;
// 		printf("redirect	| %s\n", (char *)tokens->redirect_list);
// 		return (1);
// 	}
// 	// else
// 	// {
// 	// // 	// use exam split and split on metas....
// 	// 	while (tmp)
// 	// 	{
// 	// 		tokens->redirect_list = meta_split(tmp);
// 	// 		tmp = tmp->next;
// 	// 	}
// 	// }
		
// 	/**
// 	 * 
// 	 * first, check if file is attached or not...
// 	 * if file was not attached, need to grab next node and make file var in parser()
// 	*/
// 	// if (file_attached(token_list))
// 	// {
// 	// 	// need to set current node to meta and next node to file
// 	// 	// token_list->redirect_list->meta_type = token_list->input
// 	// 	printf("token: %s", token_list->input);
// 	// 	printf("do you even work?\n");
// 	// 	token_list = token_list->next;
// 	// 	token_list->redirect_list = token_list->input;
// 	// }


// 	/**
// 	 * if i use char *files, need to init it
// 	*/ 

// 	/**
// 	 * need to put all into redir struct and in correct variable ( in correct order, at correct time...)
// 	*/

// 	/**
// 	 * if file is attached to redir
// 	 * separate redirect from file and then initalise them separately in redirects list
// 	*/
// 	// else
// 	// {
// 		// while (tokens[i])
// 		// {
// 			// if ()
			
// 		// }	
// 		// tokens->redirect_list->file = tokens->next;
// 	// }
// 	return (0);
// }

/**
 * printf("am i here?\n");
			// if (handle_redirect(token_list))
			// {
			// // if file was not attached to redir, need to grab next node and make file var
			// 	token_list = token_list->next;
			// 	token_list->redirect_list = token_list->input;
			// 	printf("redirect	| %s\n", (char *)token_list->redirect_list);
			// }
			// probably same as command, need to put the new struct vars into parser struct
			if (file_attached(token_list))
			{
				// split and init into struct vars from here and skip handle_reds?
				// reds = handle_annoying_redirects(token_list);
				printf("you forgot a fucking space\n");
			}
*/
		// // if pipe, set node in redir struct, set index to 0 for cmd vars
		// if (is_pipe(token_list))
		// {
		// 	token_list->redirect_list = token_list->input;
		// 	printf("redirect	| %s\n", (char *)token_list->redirect_list);
		// 	i = 0;
		// 	token_list = token_list->next;
		// }
		// // if 



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

	printf("tokens->redirect_list: [%s]\n", (char *)tokens->redirect_list);
	
	reds->input = tokens->redirect_list;

	printf("reds->input: [%s]\n", reds->input);

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
			printf("reds = [%s]\n", (char *)token_list->redirect_list->meta);
		}
		// if there was a redirect, need to check which so that if >, next node is file, 
		// and if pipe, next is command ( don't use index anymore, just keep for first arg)

		
		// if (there was a sassy red and i need to do something with next node) ...

		
		else
		{
			cmds = handle_commands(token_list, i);
			token_list->cmd_list = cmds;
			printf("cmds = [%s]\n", (char *)token_list->cmd_list->cmd);
			printf("strs = [%s]\n", (char *)token_list->cmd_list->strs);
		}
		token_list = token_list->next;
		i++;
	}
	return (tokens);
}

