/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:40:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/11 19:49:55 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

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

// // WHY DONT I USE STRLEN??
// // get length to return to make_token() in order to create substring of parsed token into new substred token
// int		token_len(char *parsed_token)
// {
// 	int	i;

// 	i = 0;
// 	while (parsed_token[i])
// 		i++;
// 	return (i);
// }
