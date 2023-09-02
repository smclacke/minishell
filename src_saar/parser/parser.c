/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/02 22:56:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

static void	init_stuff(t_command *cmds)
{
	cmds->strs = NULL;
	cmds->cmd = NULL;
}	

/**
 * is redirect in any of the node?
*/
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
	return (false);
}

/**
 * is redirect the only thing in node? ( file is not attached )
*/
// static bool	file_attached(t_parser *tokens)
// {
// 	if (!tokens)
// 		return (false);
// 	if (ft_strcmp(tokens->input, ">>") == 0)
// 		return (true);
// 	else if (ft_strcmp(tokens->input, "<<") == 0)
// 		return (true);
// 	else if (ft_strcmp(tokens->input, ">") == 0)
// 		return (true);
// 	else if (ft_strcmp(tokens->input, "<") == 0)
// 		return (true);
// 	return (false);
// }

/**
 * function for when redirect is attached (no space) to file
 * separate from file, put redirect and file nodes into correct part of redir struct 
*/
static void	handle_redirect(t_parser *tokens)
{
	// int	i = 0;

	/**
	 * first, check if file is attached or not...
	 * if file was not attached, need to grab next node and make file var in parser()
	*/
	// if (file_attached(token_list))
	// {
	// 	// need to set current node to meta and next node to file
	// 	// token_list->redirect_list->meta_type = token_list->input
	// 	printf("token: %s", token_list->input);
	// 	printf("do you even work?\n");
	// 	token_list = token_list->next;
	// 	token_list->redirect_list = token_list->input;
	// }

	/**
	 * if i use char *files, need to init it
	*/ 


	/**
	 * need to put all into redir struct and in correct variable ( in correct order, at correct time...)
	*/
	tokens->redirect_list = tokens->input;
	printf("redirect: %s\n", (char *)tokens->redirect_list);


	/**
	 * if file is attached to redir
	 * separate redirect from file and then initalise them separately in redirects list
	*/
	if (!tokens)
		exit(EXIT_FAILURE); // dunno, do something when error handling
	// else
	// {
		printf("test\n");
		// while (tokens[i])
		// {
			// if ()
			
		// }	
		// tokens->redirect_list->file = tokens->next;
	// }
}

/**
 * first node in list, if not redirc, cmd
 * first thing after pipe, if not redirec, cmd (right?)
 * everything else string
*/
static void	handle_commands(t_parser *tokens, int i)
{
	t_command		*cmds;
		
	cmds = (t_command *)malloc(sizeof(t_command));
	if (!cmds)
		exit(EXIT_FAILURE); // fix this later
	init_stuff(cmds);
	tokens->cmd_list = tokens->input;
	cmds->info = tokens->cmd_list;

	// the one that must be a cmd (i think maybe, ask someone knowledgable about this)
	if (i == 0)
	{	
		cmds->cmd = cmds->info;
		printf("cmds->cmd: %s\n", cmds->cmd);
	}
	else
	{
		cmds->strs = cmds->info;
		printf("cmds->strs: %s\n", cmds->strs);
	}
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
	int				i = 0;

	token_list = tokens;
	while (token_list)
	{
		// if pipe, set node in redir struct, set index to 0 for cmd vars
		if (ft_strcmp(token_list->input, "|") == 0)
		{
			token_list->redirect_list = token_list->input;
			printf("redirect: %s\n", (char *)token_list->redirect_list);
			i = 0;
			token_list = token_list->next;
		}
		if (parser_redirect(token_list))
			handle_redirect(token_list);
			// if file was not attached to redir, need to grab next node and make file var
		else
			handle_commands(token_list, i);
		token_list = token_list->next;
		i++;
	}
	return (tokens);
}

