/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:45:59 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/07 18:08:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo errors, 54 return needs error
*/

int	is_meta(char *input)
{
	if (ft_strnstr(input, MOREMORE, 2))
		return (2);
	else if (ft_strnstr(input, LESSLESS, 2))
		return (2);
	else if (ft_strnstr(input, MORE, 1))
		return (1);
	else if (ft_strnstr(input, LESS, 1))
		return (1);
	else if (ft_strnstr(input, PIPE, 1))
		return (1);
	return (0);
}

int	space_or_meta(int c)
{
	if (ft_isspace(c) || ft_ismeta(c))
		return (c);
	return (0);
}

int	is_same_quote(int c, char *quote_type)
{
	if (c == *quote_type)
		return (1);
	return (0);
}

char	*which_quote(char *input)
{
	if (ft_strnstr(input, SINGLE_Q, 1))
		return (SINGLE_Q);
	else if (ft_strnstr(input, DOUBLE_Q, 1))
		return (DOUBLE_Q);
	return (0);
}

/**
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
int	next_quote(char *input, char c)
{
	int	i;

	i = 1;
	while (input[i] && input[i] != c)
		i++;
	if (input[i] != c)
	{
		printf("ERROR UNCLOSED QUOTES\n"); // need to change to proper error func
		exit(1);
	}
	return (i);
}
