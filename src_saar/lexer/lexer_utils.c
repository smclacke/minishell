/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:40:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/14 12:49:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

// parse space
void	parse_space(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
}

// print tokens
t_list	*ft_print_tokens(t_list *token)
{
	t_list	*list;
	
	list = token;
	while (list)
	{
		printf("token: %s\n", list->content);
		list = list->next;
	}
	return (token);
}
