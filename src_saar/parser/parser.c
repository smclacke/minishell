/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/02 22:34:54 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

static void	init_stuff(t_command *cmds)
{
	cmds->strs = NULL;
	cmds->cmd = NULL;
}	

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
	return (false);
}

/**
 * function for when redirect is attached (no space) to file
 * separate from file, put redirect and file nodes into correct part of redir struct 
*/
static void	handle_redirect(t_parser *tokens)
{
	// int	i = 0;

	// if i use char *files, need to init it
	tokens->redirect_list = tokens->input;
	// need to put all into redir struct and in correct variable

	if (!tokens)
		exit(EXIT_FAILURE); // dunno, do something when error handling
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
static void	handle_commands(t_parser *tokens, int i)
{
	t_command		*cmds;
		
	cmds = (t_command *)malloc(sizeof(t_command));
	if (!cmds)
		exit(EXIT_FAILURE); // fix this later
	init_stuff(cmds);
	tokens->cmd_list = tokens->input;
	cmds->info = tokens->cmd_list;
	printf("cmds->info: %s\n", cmds->info);

	// first one cmd
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
		// if pipe, set node in redir struct, set index to 0 
		if (ft_strcmp(token_list->input, "|") == 0)
		{
			token_list->redirect_list = token_list->input;
			i = 0;
			token_list = token_list->next;
		}
		if (parser_redirect(token_list))
		{
			if (!file_attached(token_list)) // dettached files are still becoming cmd strs
			{
				// need to set current node to meta and next node to file
				// token_list->redirect_list->meta_type = token_list->input
				token_list = token_list->next;
				token_list->redirect_list = token_list->input;
				token_list = token_list->next;
			}
			else
				handle_redirect(token_list);
		}
		else
			handle_commands(token_list, i);
		token_list = token_list->next;
		i++;
	}
	return (tokens);
}

