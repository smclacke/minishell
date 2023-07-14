/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:40:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/11 21:21:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

// parse space
void	parse_space(char *input)
{
	while (ft_isspace(*input))
		input++;
}

/**
 * find next quotation
 * if unclosed, throw error
*/
// int	second_quote(char *input, char c)
// {
// 	int	i;

// 	i = 1;
// 	while (input[i] != c && input[i])
// 		i++;
// 	if (!input[i])
// 		return (0);
// 	return (i);
// }

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
