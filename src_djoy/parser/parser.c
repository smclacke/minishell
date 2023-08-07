/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:14:07 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/07 15:11:32 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

// DONT REMOVE CAPS OR QUOTES, JUST MAKE THE BEST TOKENS I CAN AND EXECVE AND PATH CMP WILL DO THE REST

/**
 * @brief	assigns the tokens to a member in the parser struct:
 * 			meta, cmd, absolute path or anything else str
 * @param	tokens passed from the lexer
 * @param	parser_struct  structure to assign each token to the correct member within parser struct
 * @return	assigns the token input to a member in the parser struct
*/
static void	*parser_define_tokens(t_lexer *tokens, t_parser *parser_struct)
{
	if (!tokens)
		return (false);
	if (parser_cmp_metas(tokens))
	{
		parser_struct->meta = tokens->input;
		printf("arg->meta:	~: %s\n", parser_struct->meta);
	}
	else if (parser_cmp_builtins(tokens))
	{
		parser_struct->cmd = tokens->input;
		printf("arg->cmd:	~: %s\n", parser_struct->cmd);
	}
	else if (parser_cmp_abso(tokens))
	{
		parser_struct->abso = tokens->input;
		printf("arg->abso:	~: %s\n", parser_struct->abso);
	}
	else
	{
		parser_struct->str = tokens->input;
		printf("arg->str:	~: %s\n", parser_struct->str);
	}
	return (NULL);
}

void	init_parser(t_parser *parser_struct)
{
	parser_struct->str = NULL;
	parser_struct->cmd = NULL;
	parser_struct->meta = NULL;
	parser_struct->abso = NULL;
}

/**
 * @brief	Main parser function:
			Check the tokens to see which member of the parser struct they need to be sorted into
			Return the new parser_struct to the expander
 * @param	tokens t_lexer tokens passed from the lexer to be sorted by the parser
 * @return	parser_struct: all the tokens given by the lexer have been sorted into the parser struct. The first argument is checked for its validity
*/
t_parser	*parser(t_lexer *tokens)
{
	t_parser	*parser_struct;
	t_parser	*parser_node;

	parser_struct = NULL;
	parser_node = NULL;
	while (tokens)
	{
		parser_node = parser_listnew(tokens);
		parser_listadd_back(&parser_struct, parser_node);
		tokens = tokens->next;
	}
	return (parser_struct);
}

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
*/
void	print_parser_list(t_parser *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
		printf("iterations [%d]\n", i);
	}
}
//make a lstaddback for myself hehe

t_parser		*parser_listlast(t_parser *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	return (list);
}

void	parser_listadd_back(t_parser **list, t_parser *new)
{
	t_parser	*last;

	if (*list)
	{
		last = parser_listlast(*list);
		last->next = new;
	}
	else
		*list = new;
}

t_parser	*parser_listnew(t_lexer *tokens)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(*new));
	if (!new)
		return (0);
	init_parser(new);
	parser_define_tokens(tokens, new);
	new->next = NULL;
	return (new);
}

// // print the tokens for testing purposes
// t_parser	*print_parser(t_parser *token)
// {
// 	t_parser	*list;

// 	list = token;
// 	while (list)
// 	{
// 		printf("lexer: \t\t~: %s\n", list->input);
// 		list = list->next;
// 	}
// 	return (token);
// }