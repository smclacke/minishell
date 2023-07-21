/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:40:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/21 13:48:59 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/sarah.h"

// t_lexer version
t_lexer		*list_last(t_lexer *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	return (list);
}

// t_lexer version
void	listadd_back(t_lexer **list, t_lexer *new)
{
	t_lexer	*last;

	if (*list)
	{
		last = list_last(*list);
		last->next = new;
	}
	else
		*list = new;
}

// t_lexer version
t_lexer	*list_new(void *input)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(*new));
	if (!new)
		return (0);
	new->input = input;
	new->next = 0;
	return (new);
}

// parse space I DONT THINK I NEED THIS ANYMORE SINCE IM USING SPLIT BUT KEEP FOR LATER
void	parse_space(char *input)
{
	while (ft_isspace(*input))
		input++;
}

// print tokens
t_lexer	*ft_print_tokens(t_lexer *token)
{
<<<<<<< HEAD
	t_list	*list;

=======
	t_lexer	*list;
	
>>>>>>> 14d6cd01162695da7e46a7e9f20f6591e7c9585f
	list = token;
	while (list)
	{
		printf("token: %s\n", list->input);
		list = list->next;
	}
	return (token);
}
